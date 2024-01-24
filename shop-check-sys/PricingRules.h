#pragma once

#include <unordered_map>
#include <memory>
#include "Item.h"

struct SpecialPrice
{
	size_t amt = 0;
	double price = 0;
};
class PricingRules
{
public:
	void addSpecialPrice(const Item& itm, const SpecialPrice &special);
	double price(std::string name,size_t amt, double price);
protected:
	std::unordered_map<std::string, SpecialPrice> specialPrices;
};

typedef std::shared_ptr<PricingRules> shPricingRules;