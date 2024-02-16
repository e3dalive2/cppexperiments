//You are playing a video game. Your screen can be represented as a 2D array, where 0s represent walkable areas and 1s represent non-walkable areas. 
//You are currently searching for the entrance to a cave that is located on the right side of the screen. Your character starts anywhere in the leftmost column.
//Create a function that determines if you can enter the cave.You can only move left, right, up, or down(not allowed to move diagonally).


#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <deque>

using Vec2d = std::vector<std::vector<int>>;


struct Pos
{
	int x;
	int y;

	bool operator==(const Pos& o) const {
		return x == o.x && y == o.y;
	}
};

Pos operator+(Pos a, const Pos& b) {
	a.x += b.x;
	a.y += b.y;
	return a;
}

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

	void load(const Vec2d& other)
	{
		m_data = other;
		for (int h = 0; h < m_data.size(); h++)
		{
			auto& slice = m_data[h];
			maxWidth = std::max(maxWidth, slice.size());
		}
	}

	std::vector< std::vector<int>> m_data;
	size_t maxWidth = 0;
};

class CField
{
public:
	CField(const Vec2d& other)
	{
		m_vec2d.load(other);
	}

	void set(const Pos& pos, int value)
	{
		m_vec2d.set(pos, value);
	}

	void print() const
	{
		m_vec2d.print();
	}

	bool isNearCave(const Pos& pos) const
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

		std::vector<Pos> directions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // Up, Down, Left, Right


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

			if (isNearCave(cur)) // found the end
			{
				m_path.set(cur, 2);
				found = true;
				break;//finished
			}



			auto curSz = todo.size();

			m_path.set(cur, 2);


			for (const auto& dir : directions) {
				Pos newPos = cur + dir;

				Pos regionEnd{ m_vec2d.getMaxWidth() ,m_vec2d.getMaxHeight() };
				if (newPos.x < 0 || newPos.y < 0) continue;//ignore out of bounds
				if (newPos.x >= regionEnd.x || newPos.y >= regionEnd.y) continue;
				todo.push_back(newPos);
			}

			//std::cout << "added " << todo.size() - curSz << "\n";
		}


		if (found)
		{
			m_path.print();
		}
		else
		{
			std::cout << "path not found\n";
		}

		return found;
	}

protected:
	CAutoArray2D m_vec2d;
};

//Simple data sets

constexpr auto kDataW = 8;
constexpr auto kDataH = 4;

Vec2d data{
	{0, 0, 1, 1, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0 }
};

Vec2d data2{
	{0, 1, 1, 1, 0, 1, 1, 0},
	{ 0, 0, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 0 }
};

Vec2d data3{
	 {0, 1, 1, 1, 1, 1, 1, 1},
	 {0, 0, 0, 0, 1, 0, 0, 1},
	 {0, 0, 1, 0, 1, 0, 0, 0},
	 {0, 1, 1, 0, 0, 0, 1, 0}
};

void main()
{
	{
		CField field{ data };
		field.print();
		field.findCaveBrute({ 0,0 });
		std::cout << std::endl;
	}


	{
		CField field{ data2 };
		field.print();
		field.findCaveBrute({ 0,0 });
		std::cout << std::endl;
	}

	{
		CField field{ data3 };
		field.print();
		field.findCaveBrute({ 0,0 });
		std::cout << std::endl;
	}
}