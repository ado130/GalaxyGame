#ifndef SIMPLETRADEGOODS_H
#define SIMPLETRADEGOODS_H

#include "itradableitem.hh"

#include <string>

class SimpleTradeGoods : ITradableItem
{
public:
    SimpleTradeGoods(std::string name, int price) : name_(name), price_(price) {}

    // IItemInGalaxy interface
public:
    std::string getName() { return name_; }

    // ITradableItem interface
public:
    int getPrice() { return price_; }
private:
    std::string name_;
    int price_;
};

#endif // SIMPLETRADEGOODS_H
