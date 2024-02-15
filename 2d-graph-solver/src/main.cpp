//You are playing a video game. Your screen can be represented as a 2D array, where 0s represent walkable areas and 1s represent non-walkable areas. 
//You are currently searching for the entrance to a cave that is located on the right side of the screen. Your character starts anywhere in the leftmost column.
//Create a function that determines if you can enter the cave.You can only move left, right, up, or down(not allowed to move diagonally).


#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <deque>


struct Pos
{
	int x;
	int y;
};

// This is simple automatically sized array which grows to accumulate needs for memory
class CAutoArray2D
{
public:
	void set(const Pos& pos, int value, int defVal = 0)
	{
		prepare(pos, defVal);
		m_data[pos.y][pos.x] = value;
	}

	void prepare(const Pos& pos, int defVal = 0)
	{
		if (pos.y >= m_data.size())
		{
			m_data.resize(pos.y + 1);
		}
		auto& slice = m_data[pos.y];
		if (pos.x >= slice.size())
		{
			slice.resize(pos.x + 1, defVal);
			maxWidth = std::max(maxWidth, slice.size());
		}
	}

	int get(const Pos& pos)
	{
		if (pos.y < 0 || pos.x < 0) return -1;

		prepare(pos);
		return m_data[pos.y][pos.x];
	}

	int read(const Pos& pos) const
	{
		if (pos.y < 0 || pos.x < 0) return -1;
		if (pos.x >= getMaxWidth() || pos.y >= getMaxHeight()) return -1;
		return m_data[pos.y][pos.x];
	}


	int getMaxWidth() const
	{
		return maxWidth;
	}

	int getMaxHeight() const
	{
		return m_data.size();
	}

	void print() const
	{
		for (int h = 0; h < m_data.size(); h++)
		{
			auto& slice = m_data[h];
			for (int w = 0; w < slice.size(); w++)
			{
				auto& pt = slice[w];
				std::cout << (/*pt == 0 ? " " : */std::to_string(pt)) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void load(const CAutoArray2D& other)
	{
		m_data = other.m_data;
		maxWidth = other.maxWidth;
	}

	std::vector< std::vector<int>> m_data;
	size_t maxWidth = 0;
};

class CField
{
public:

	void set(const Pos& pos, int value)
	{
		m_vec2d.set(pos, value);
	}

	void print() const
	{
		m_vec2d.print();
	}

	bool isNearCave(const Pos& pos)
	{
		return pos.x == m_vec2d.getMaxWidth() - 1;
	}

	static bool isWalkable(int value)
	{
		return value == 0;
	}

	bool findCaveBrute(const Pos& startPos)
	{
		std::deque<Pos> todo;

		CAutoArray2D m_visited;

		todo.push_back(startPos);

		CAutoArray2D m_path;
		m_path.load(m_vec2d);//for viz load base data

		bool found = false;

		while (!todo.empty())
		{
			auto& cur = todo.front();
			todo.pop_front();

			if (m_visited.get(cur) == 1)
			{
				//std::cout << "been in " << cur.x << "/" << cur.y << "\n";
				continue;//ignore visited
			}

			auto value = m_vec2d.read(cur);
			if (value == -1) continue;
			//std::cout << "visiting " << cur.x << "/" << cur.y << " = " << value << "\n";

			m_visited.set(cur, 1);

			if (!isWalkable(value)) continue;//can't walk here

			if (isNearCave(cur))
			{
				m_path.set(cur, 2);
				found = true;
				break;//finished
			}

			auto curSz = todo.size();

			m_path.set(cur, 2);



			if (cur.x < m_vec2d.getMaxWidth())
			{
				todo.push_back({ cur.x + 1,cur.y });//right
			}

			if (cur.y < m_vec2d.getMaxHeight())
			{
				todo.push_back({ cur.x,cur.y + 1 });//bottom
			}

			if (cur.x > 0)
			{
				todo.push_back({ cur.x - 1,cur.y });//left
			}

			if (cur.y > 0)
			{
				todo.push_back({ cur.x,cur.y - 1 });//top
			}

			//std::cout << "added " << todo.size() - curSz << "\n";
		}


		if (found)
		{
			m_path.print();
		}

		return found;
	}

protected:
	CAutoArray2D m_vec2d;
};

//Simple data sets

constexpr auto kDataW = 8;
constexpr auto kDataH = 4;

int data[kDataH][kDataW]{
	{0, 0, 1, 1, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0 }
};

int data2[kDataH][kDataW]{
	{0, 1, 1, 1, 0, 1, 1, 0},
	{ 0, 0, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 0 }
};

int data3[kDataH][kDataW]{
	 {0, 1, 1, 1, 1, 1, 1, 1},
	 {0, 0, 0, 0, 1, 0, 0, 1},
	 {0, 0, 1, 0, 1, 0, 0, 0},
	 {0, 1, 1, 0, 0, 0, 1, 0}
};

void main()
{
	CField field;
	for (int h = 0; h < kDataH; h++)
	{
		for (int w = 0; w < kDataW; w++)
		{
			field.set({ w,h }, data3[h][w]);
		}
	}
	field.print();
	field.findCaveBrute({ 0,0 });


}