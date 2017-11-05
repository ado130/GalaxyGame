#ifndef ITRADABLEITEM_H
#define ITRADABLEITEM_H

#include "iitemingalaxy.hh"
#include <string>

class ITradableItem : IItemInGalaxy
{
public:
    virtual int getPrice() = 0;
};

#endif // ITRADABLEITEM_H
