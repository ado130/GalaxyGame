#ifndef ITRADABLEITEM_H
#define ITRADABLEITEM_H

#include "iitemingalaxy.hh"
#include <string>

namespace Student {

/**
 * @brief Every item in galaxy, which can be put into player's inventory
 * and has a price (so that it can be traded with) has to inplement this class
 */
class ITradableItem : IItemInGalaxy
{
public:
    /**
     * @brief Every tradable item in galaxy has to have a price
     * @return price of the item
     * @post Exception guarantee: nothrow
     */
    virtual int getPrice() = 0;
};
}

#endif // ITRADABLEITEM_H
