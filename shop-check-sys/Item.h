#pragma once

#include <string>

class Item
{
public:
	Item(std::string name, double price);
	std::string name() const;
	double price() const;
protected:
	std::string _name;
	double _price;
};

