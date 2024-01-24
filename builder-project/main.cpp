
#include <Builder.h>

#include <iostream>
#include <chrono>
#include <sstream>

void fun(int id, std::chrono::milliseconds ms)
{
	// Reduce ruining the output with multiple threads
	std::stringstream ss;

	ss << "[" << std::this_thread::get_id() << "] -> Building target " << id << "\n";
	std::cout << ss.str();
	std::this_thread::sleep_for(ms);
}


int main()
{
	using namespace std::chrono;

	// build test 1
	BuildGraph test_graph1;
	{
		std::chrono::milliseconds testDelay = 1s;
		test_graph1.add_target(1, { 2,4 }, [&] { fun(1, testDelay); });
		test_graph1.add_target(2, { 3 }, [&] { fun(2, testDelay); });
		test_graph1.add_target(3, {  }, [&] { fun(3, testDelay); });
		test_graph1.add_target(4, { 5 }, [&] { fun(4, testDelay); });
		test_graph1.add_target(5, {  }, [&] { fun(5, testDelay); });
	}

	// build bad test 2
	BuildGraph test_graph2;
	{
		test_graph2.add_target(1, { 2 }, [] { fun(1, 1s); });
		test_graph2.add_target(2, { 3 }, [] { fun(2, 1s); });
		test_graph2.add_target(3, { 4 }, [] { fun(3, 1s); });
		test_graph2.add_target(4, { 2 }, [] { fun(4, 1s); });
	}

	// add another test
	BuildGraph graph;
	{
		graph.add_target(1, { 2, 3 }, [] { fun(1, 200ms); });
		graph.add_target(2, { 3, 4 }, [] { fun(2, 100ms); });
		graph.add_target(3, { 4 }, [] { fun(3, 400ms); });
		graph.add_target(4, { }, [] { fun(4, 600ms); });
		graph.add_target(5, { 1 }, [] { fun(5, 100ms); });
	}

	try {
		Builder builder(2);
		builder.execute(test_graph1, 1);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << "\n";
	try {
		Builder builder(1);
		builder.execute(test_graph2, 4);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << "\n";
	try {
		Builder builder(std::thread::hardware_concurrency());
		builder.execute(graph, 5);
		std::cout << "\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	system("pause");

}

