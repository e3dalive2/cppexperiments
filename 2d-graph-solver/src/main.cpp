#include <iostream>
#include <string>

constexpr auto kDataW = 8;
constexpr auto kDataH = 4;

struct Pos
{
	int x;
	int y;
};

int data[kDataH][kDataW]{
	{0, 0, 1, 1, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0 }
};

int GetData(const Pos& pos)
{
	if (pos.x<0 || pos.x>kDataW) return -1;
	if (pos.y<0 || pos.y>kDataH) return -1;
	return data[pos.y][pos.x];
}

void printField()
{
	for (int h = 0; h < kDataH; h++)
	{
		for (int w = 0; w < kDataW; w++)
		{
			int id = GetData({ w,h });
			std::cout << std::to_string(id) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void main()
{
	printField();
}