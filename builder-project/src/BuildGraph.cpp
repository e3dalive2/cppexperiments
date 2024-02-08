
#include <BuildGraph.h>

void BuildGraph::add_target(size_t id, TargetDeps dependencies, std::function<void()> task)
{
	if (targets_.find(id) != targets_.end()) {
		throw std::runtime_error("Target with this ID " + std::to_string(id) + " already exists.");
	}
	targets_[id] = { id, task, dependencies };// add it

	// Fiil our structure on add instead of post-processing
	in_degree_[id] = dependencies.size();
	for (auto& dep : dependencies) {
		graph_[dep].push_back(id);
	}
}

Target BuildGraph::get_target(size_t id) const
{
	auto it = targets_.find(id);
	if (it == targets_.end()) {
		throw std::runtime_error("Target with this ID: " + std::to_string(id) + " does not exist.");
	}
	return it->second;
}

TargetDeps BuildGraph::get_deps(size_t id) const
{
	auto graphNode = graph_.find(id);
	if (graphNode != graph_.end())
	{
		return graphNode->second;
	}
	return {};
}

GraphInDegree BuildGraph::getInDegree() const
{
	return in_degree_;
}

bool BuildGraph::detect_cycle_util(size_t node, TargetsSet& visited, TargetsSet& rec_stack) const {
	if (visited.find(node) == visited.end()) {
		visited.insert(node);
		rec_stack.insert(node);

		const auto graphNode = get_deps(node);
		if (!graphNode.empty())
		{
			for (const auto& adj : graphNode) {
				if (visited.find(adj) == visited.end() && detect_cycle_util(adj, visited, rec_stack))
					return true;
				else if (rec_stack.find(adj) != rec_stack.end())
					return true;
			}
		}
	}
	rec_stack.erase(node);
	return false;
}

bool BuildGraph::detect_cycle() const {
	TargetsSet visited;
	TargetsSet rec_stack;

	for (auto& pair : targets_) {
		if (detect_cycle_util(pair.first, visited, rec_stack))
			return true;
	}
	return false;
}

