#ifndef Builder_h__
#define Builder_h__

#include <BuildGraph.h>
#include <unordered_set>
#include <queue>
#include <mutex>

// Separated to remember that they are accessed by all threads inside of the builder
struct BuilderThreadVars
{
	TargetsSet in_progress_;
	GraphInDegree in_degree_;
	std::queue<size_t> build_queue_;
	std::atomic_bool working_;

	BuilderThreadVars() {}
};

class Builder {
public:
	explicit Builder(size_t num_threads) : num_threads_{ num_threads } {}

	//TODO for destructor additional stop can be added when executed is called in parallel to prevent memory access violation

	void worker_thread(const BuildGraph& build_graph);
	void execute(const BuildGraph& build_graph, size_t target_id);

private:
	size_t num_threads_;


	std::mutex mutex_;
	std::condition_variable cv_;

	BuilderThreadVars thread_vars_;
};

#endif // Builder_h__
