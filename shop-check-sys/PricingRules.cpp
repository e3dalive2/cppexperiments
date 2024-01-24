#include "PricingRules.h"

void PricingRules::addSpecialPrice(const Item& itm, const SpecialPrice &price)
{
	specialPrices[itm.name()] = price;
}


double PricingRules::price(std::string name, size_t amt, double price)
{
	auto it = specialPrices.find(name);
	if (it == specialPrices.end())
	{
		return amt * price;//no special just calculate
	}
	//estimate bonus
	auto& sp = it->second;
	double div = amt / sp.amt;//divide
	int specialAmt = (int)floor(div);//estimate amount for special price
	double lowPrice = specialAmt * sp.price;//estimate special price
	int lowAmt = specialAmt * sp.amt;//estimate amount for that price
	int remAmount = amt - lowAmt;//estimate remaining items
	return lowPrice + remAmount * price;//calculate their price
}
