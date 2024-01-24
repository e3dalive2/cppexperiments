#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "PricingRules.h"

//could have been done as array of shared_ptrs of items

struct groupInfo
{
	size_t amt;
	double price;
};

typedef std::shared_ptr<Item> shItem;
typedef std::list<Item> itemList;
class Checkout
{
public:
	Checkout(shPricingRules& rules);
	void scan(const Item& itm);
	bool remove(const Item& itm);
	double price();
protected:

	std::unordered_map<std::string, groupInfo> grouper;
	shPricingRules _rules;
};

