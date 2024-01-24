#ifndef Target_h__
#define Target_h__

#include <functional>
#include <vector>

struct Target {
	size_t id;
	std::function<void()> task;
	std::vector<size_t> dependencies;
};

#endif // Target_h__
