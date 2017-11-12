#ifndef SIMPLETRADEGOODS_H
#define SIMPLETRADEGOODS_H

#include "itradableitem.hh"

#include <string>

class SimpleTradeGoods : ITradableItem
{
public:
    SimpleTradeGoods() : name_(""), price_(0) {}
    SimpleTradeGoods(std::string name, int price) : name_(name), price_(price) {}

    bool operator==(const SimpleTradeGoods& a)
    {
        return (a.name_ == name_ && a.price_ == price_);
    }
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

