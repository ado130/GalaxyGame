#ifndef SIMPLETRADEGOODS_H
#define SIMPLETRADEGOODS_H

#include "itradableitem.hh"

#include <string>

namespace Student {

/**
 * @brief SimpleTradeGoods class represents items which can be put into player's
 * inventory and has a price (it can be traded with them)
 */
class SimpleTradeGoods : ITradableItem
{
public:
    /**
     * @brief Constructor
     * @note Creates "empty" item with no specified name and zero price
     */
    SimpleTradeGoods() : name_(""), price_(0) {}

    /**
     * @brief Constructor
     * @param name name of item
     * @param price price of item
     */
    SimpleTradeGoods(std::string name, int price) : name_(name), price_(price) {}

    //! operator '==' used for comparing equality of SimpleTradeGoods objects
    bool operator==(const SimpleTradeGoods& a)
    {
        return (a.name_ == name_ && a.price_ == price_);
    }
    // IItemInGalaxy interface
public:
    /**
     * @brief getName returns name of goods
     * @return name
     */
    std::string getName() { return name_; }

    // ITradableItem interface
public:
    /**
     * @brief getPrice returns price of goods
     * @return price
     */
    int getPrice() { return price_; }
private:
    //! item name
    std::string name_;

    //! item price
    int price_;
};
}

#endif // SIMPLETRADEGOODS_H

