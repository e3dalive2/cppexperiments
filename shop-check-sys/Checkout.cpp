#include "Checkout.h"


Checkout::Checkout(shPricingRules &rules):_rules(rules)
{

}

void Checkout::scan(const Item& itm)
{
	auto& nfo = grouper[itm.name()];
	nfo.amt++;
	nfo.price = itm.price();
}

bool Checkout::remove(const Item& itm)
{
	auto& inItem = grouper[itm.name()];
	if (inItem.amt == 0) return false;
	inItem.amt--;
	if (inItem.amt == 0)//remove empty
	{
		grouper.erase(itm.name());
	}
	return true;

}

double Checkout::price()
{
	double total = 0;
	for (std::pair<std::string, groupInfo> el : grouper)
	{
		groupInfo& nfo = el.second;
		total += _rules->price(el.first, nfo.amt,nfo.price);
	}
	return total;
}
