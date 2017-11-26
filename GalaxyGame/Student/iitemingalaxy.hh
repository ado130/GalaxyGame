#ifndef IITEMINGALAXY_HH
#define IITEMINGALAXY_HH

#include <string>

namespace Student {

/**
 * @brief Every item in galaxy, which can be put into player's inventory
 * have to inplement this class
 */
class IItemInGalaxy
{
public:
    /**
     * @brief Every item in galaxy has to have a name
     * @return name of the item
     * @post Exception guarantee: nothrow
     */
    virtual std::string getName() = 0;
};
}

#endif // IITEMINGALAXY_HH
