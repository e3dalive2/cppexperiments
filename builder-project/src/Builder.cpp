
#include <Builder.h>

void Builder::worker_thread(const BuildGraph& build_graph) {
	while (thread_vars_.working_) {
		size_t current_id;
		{
			std::unique_lock<std::mutex> lock(mutex_);

			cv_.wait(lock, [this] { return !thread_vars_.build_queue_.empty() || thread_vars_.in_progress_.empty(); });

			auto& in_progress = thread_vars_.in_progress_;
			auto& build_queue = thread_vars_.build_queue_;
			if (build_queue.empty() && in_progress.empty()) {
				break; // Queue is finished
			}

			current_id = build_queue.front();
			build_queue.pop();
			in_progress.insert(current_id);
		}

		// Execute the build task for the current target
		build_graph.get_target(current_id).task();

		// Update in-progress and in-degree for dependencies
		{
			std::unique_lock<std::mutex> lock(mutex_);
			auto& in_progress = thread_vars_.in_progress_;
			in_progress.erase(current_id);

			const auto graphNode = build_graph.get_deps(current_id);

			auto& in_degree = thread_vars_.in_degree_;
			auto& build_queue = thread_vars_.build_queue_;

			for (const auto& dep : graphNode) {
				if (--in_degree[dep] == 0) {
					build_queue.push(dep);
				}
			}
			cv_.notify_all();
		}
	}
}

void Builder::execute(const BuildGraph& build_graph, size_t target_id)
{
	// First, check for cycles in the graph
	if (build_graph.detect_cycle())
	{
		throw std::exception("Cycle detected in the build graph");
	}

	if (num_threads_ == 0)
	{
		throw std::exception("Invalid number of threads");
	}

	if (thread_vars_.working_)
	{
		throw std::exception("Duplicate dispatch");
	}

	// Add targets with zero in-degree to the build queue
	thread_vars_.in_degree_ = build_graph.getInDegree();
	for (auto& pair : thread_vars_.in_degree_) {
		if (pair.second == 0) {
			thread_vars_.build_queue_.push(pair.first);
		}
	}

	// Start worker threads
	thread_vars_.working_ = true;
	thread_vars_.in_progress_.clear();

	std::vector<std::thread> workers;
	for (size_t i = 0; i < num_threads_; ++i) {
		workers.emplace_back(&Builder::worker_thread, this, std::ref(build_graph));
	}

	// Join worker threads
	for (auto& worker : workers) {
		worker.join();
	}

	thread_vars_.working_ = false;
}

