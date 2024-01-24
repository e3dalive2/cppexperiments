// ShopCheckSys.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Checkout.h"
#include "Item.h"
#include "PricingRules.h"

int main()
{

    Item itemA("A", 50);
    Item itemB("B", 30);
    Item itemC("C", 20);
    Item itemD("D", 15);

    auto rules=std::make_shared<PricingRules>();
    rules->addSpecialPrice(itemA, { 3,130 });
    rules->addSpecialPrice(itemB, { 2,45 });

    std::unique_ptr< Checkout> checkout = std::make_unique< Checkout>(rules);
    checkout->scan(itemA);
    checkout->scan(itemB);
    checkout->remove(itemA);
    auto priceSoFar = checkout->price();
    std::cout << "priceSoFar: " << priceSoFar << "\n";
    checkout->scan(itemB);
    checkout->scan(itemD);
    checkout->scan(itemA);
    checkout->scan(itemA);
    checkout->scan(itemA);
    auto totalPrice = checkout->price();
    std::cout << "totalPrice: " << totalPrice << "\n";
    system("pause");
}

