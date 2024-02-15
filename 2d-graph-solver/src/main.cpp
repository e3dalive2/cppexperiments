//You are playing a video game. Your screen can be represented as a 2D array, where 0s represent walkable areas and 1s represent non-walkable areas. 
//You are currently searching for the entrance to a cave that is located on the right side of the screen. Your character starts anywhere in the leftmost column.
//Create a function that determines if you can enter the cave.You can only move left, right, up, or down(not allowed to move diagonally).


#include <iostream>
#include <string>
#include <vector>
#include <stack>

constexpr auto kDataW = 8;
constexpr auto kDataH = 4;

struct Pos
{
	int x;
	int y;
};

class CField
{
public:
	void set(const Pos& pos, int value)
	{
		if (pos.y >= m_data.size())
		{
			m_data.resize(pos.y + 1);
		}
		auto& slice = m_data[pos.y];
		if (pos.x >= slice.size())
		{
			slice.resize(pos.x + 1);
		}
		slice[pos.x] = value;

	}

	void print() const
	{
		for (int h = 0; h < m_data.size(); h++)
		{
			auto& slice = m_data[h];
			for (int w = 0; w < slice.size(); w++)
			{
				auto& pt = slice[w];
				std::cout << std::to_string(pt) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	int getData(const Pos& pos) const
	{
		if (pos.y<0 || pos.y>m_data.size()) return -1;
		auto& slice = m_data[pos.y];
		if (pos.x<0 || pos.x>slice.size()) return -1;
		return slice[pos.x];
	}

	static bool isNearCave(const Pos& pos)
	{
		return pos.x == kDataW - 1;
	}

	static bool isWalkable(int value)
	{
		return value == 0;
	}

	void findCaveBrute(const Pos& pos) const
	{
		std::stack<Pos> todo;
	}

protected:
	std::vector< std::vector<int>> m_data;
};

int data[kDataH][kDataW]{
	{0, 0, 1, 1, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0 }
};


void main()
{
	CField field;
	for (int h = 0; h < kDataH; h++)
	{
		for (int w = 0; w < kDataW; w++)
		{
			field.set({ w,h }, data[h][w]);
		}
	}
	field.print();
	//printField();


}