#include "Item.h"

Item::Item(std::string name, double price):_name(name),_price(price)
{

}

std::string Item::name() const
{
	return _name;
}

double Item::price() const
{
	return _price;
}
