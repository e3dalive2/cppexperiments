//There are n people standing in line for a bus. They are numbered from left to right, 1 to n. 
// Each person has a patience limit, p and will only wait until the time p expires. 
// If the bus arrives after time p, the person will leave the line and miss the bus. 
// Initially the bus is empty and has a fixed capacity, k. 
//Given a number of scenarios s, where each scenario is a time of bus arrival, s[i], 
//for each scenario, print the index / number(1 - indexed) of the kth person who catches the bus.
//If all passengers remaining in the line can board the bus, return 0 because there will be no kth person.

#include <vector>
#include <iostream>

using IntVec = std::vector<int>;

int solve_per_scenario(const int peopleInLine, const IntVec& peopleTimes, const int scenario)
{
	int numThatFit = 0;
	int count = 0;
	for (size_t i = 0; i < peopleTimes.size(); i++)
	{
		auto person = peopleTimes[i];
		if (person > scenario)
		{
			count++;

			numThatFit = i + 1;
		}
	}

	if (count < peopleInLine) {
		return 0;
	}
	else {
		return numThatFit;
	}
}

void solve_bus_problem(const int peopleInLine, const IntVec& peopleTimes, const IntVec& scenarios)
{
	for (auto scen : scenarios)
	{
		std::cout << "for scenario " << scen << " ";
		int id = solve_per_scenario(peopleInLine, peopleTimes, scen);
		std::cout << id;
		std::cout << "\n";
	}
}

void main()
{
	{
		auto k = 3;
		IntVec p = { 2,5,3 };
		IntVec s = { 1,5 };
		solve_bus_problem(k, p, s);
	}

	std::cout << "\n";
	{
		auto k = 3;
		IntVec p = { 1,4,4,3,1,2,6 };
		IntVec s = { 1,2,3,4,5,6,7 };
		solve_bus_problem(k, p, s);
	}
}