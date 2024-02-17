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

	bool operator!=(const Pos& o) const {
		return x != o.x || y != o.y;
	}

	friend Pos operator+(Pos a, const Pos& b) {
		a.x += b.x;
		a.y += b.y;
		return a;
	}
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

	void fill(int value)
	{
		for (int h = 0; h < m_data.size(); h++)
		{
			auto& slice = m_data[h];
			for (int w = 0; w < slice.size(); w++)
			{
				auto& pt = slice[w];
				pt = value;
			}
		}
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

	int get(const Pos& pos, int defVal = 0)
	{
		if (pos.y < 0 || pos.x < 0) return -1;

		prepare(pos, defVal);
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
				if (pt < 0) std::cout << "  ";
				else std::cout << (/*pt == 0 ? " " : */std::to_string(pt)) << " ";
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

	bool isWalkable(const Pos& pos)
	{
		auto value = m_vec2d.read(pos);
		if (value == -1) return false;
		return isWalkable(value);
	}

	bool inBounds(const Pos& pos)
	{
		Pos regionEnd{ m_vec2d.getMaxWidth() ,m_vec2d.getMaxHeight() };
		if (pos.x < 0 || pos.y < 0) return false;//ignore out of bounds
		if (pos.x >= regionEnd.x || pos.y >= regionEnd.y) return false;
		return true;
	}

	bool findCaveBrute(const Pos& startPos)
	{
		std::deque<Pos> todo;

		Pos targetPos = { -1,-1 };

		CAutoArray2D visited;

		todo.push_back(startPos);

		CAutoArray2D m_path;
		m_path.load(m_vec2d);//for viz load base data

		bool found = false;

		std::vector<Pos> directions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // Up, Down, Left, Right

		CAutoArray2D distances;
		distances.load(m_vec2d);
		distances.fill(-1);
		distances.set(startPos, 0);

		while (!todo.empty())
		{
			auto& cur = todo.front();
			todo.pop_front();

			if (visited.get(cur) == 1)
			{
				//std::cout << "been in " << cur.x << "/" << cur.y << "\n";
				continue;//ignore visited
			}

			if (!isWalkable(cur)) continue;//can't walk here

			visited.set(cur, 1);

			if (isNearCave(cur)) // found the end
			{
				//m_path.set(cur, 2);
				targetPos = cur;
				found = true;

				break;//finished
			}

			auto curSz = todo.size();

			//m_path.set(cur, 2);

			for (const auto& dir : directions) {
				Pos newPos = cur + dir;

				if (!inBounds(newPos) || !isWalkable(newPos)) continue;//ignore blocked

				auto curDistance = distances.get(cur);
				if (distances.get(newPos) == -1)
				{
					distances.set(newPos, curDistance + 1, 0);
				}


				todo.push_back(newPos);
			}

			//std::cout << "added " << todo.size() - curSz << "\n";
		}


		if (found) // now print the path if we have it
		{
			std::stack<Pos> stack;
			stack.push(targetPos);
			while (!stack.empty())
			{
				auto cur = stack.top();
				stack.pop();

				int curDist = distances.get(cur);

				m_path.set(cur, 2);

				for (const auto& dir : directions) {
					Pos newPos = cur + dir;

					auto newDist = distances.get(newPos);
					if (!inBounds(newPos) || newDist == -1) continue;//skip bad ones
					if (newDist == curDist - 1) // we must only add those who is -1 lower then current dist
					{
						stack.push(newPos);
					}
				}
			}

			m_path.print();
			//distances.print();

			//m_path.print();
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