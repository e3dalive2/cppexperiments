#ifndef BuildGraph_h__
#define BuildGraph_h__

#include <Target.h>

#include <unordered_map>
#include <stdexcept>
#include <unordered_set>
#include <string>

using TargetsSet = std::unordered_set<size_t>;
using TargetsMap = std::unordered_map<size_t, Target>;
using TargetDeps = std::vector<size_t>;
using GraphInDegree = std::unordered_map<size_t, size_t>;
using Graph = std::unordered_map<size_t, TargetDeps>;

class BuildGraph {
public:

	void add_target(size_t id, TargetDeps dependencies, std::function<void()> task);

	// Return target from the list
	Target get_target(size_t id) const;

	// Returns calculated target dependencies form the graph
	TargetDeps get_deps(size_t id) const;

	// Returns in-degree list
	GraphInDegree getInDegree() const;

	// Detects cyclic references
	bool detect_cycle() const;

private:
	Graph graph_;
	GraphInDegree in_degree_;
	TargetsMap targets_;

	// Internal helper for detect_cycle
	bool detect_cycle_util(size_t node, TargetsSet& visited, TargetsSet& rec_stack) const;

};


#endif // BuildGraph_h__
