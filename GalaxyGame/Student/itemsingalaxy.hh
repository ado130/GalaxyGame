#ifndef ITEMSINGALAXY_HH
#define ITEMSINGALAXY_HH

#include "iitemingalaxy.hh"
#include "simpletradegoods.hh"

#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <memory>

namespace Student {

/**
 * @brief Class responsible for loading and storing all items which
 * can be used in galaxy
 */
class ItemsInGalaxy
{
public:
    /**
     * @brief Constructor.
     * @note Object is created but no items are loaded yet.
     */
    ItemsInGalaxy();

    /**
     * @brief getSimpleTradeGoods.
     * @return Vector of all SimpleTradeGoods which can be used
     * in galaxy
     */
    std::vector<SimpleTradeGoods> getSimpleTradeGoods();
    /**
     * @brief getRandomTradeGoods ramdomly picks one object of SimpleTradeGoods
     * from simpleTradeGoods_ vector
     * @return random SimpleTradeGoods object
     * in galaxy
     */
    SimpleTradeGoods getRandomTradeGoods();

private:
    /**
     * @brief loadFromFile loads file from given filename in ASSET_FOLDER
     * @param filename name of the file
     * @return QJsonArray of loaded items
     * @exception throws IoException if file cannot be read
     * @exception thorws FormatException if file cannot be parsed to json
     * @post Exception guarantee: strong
     */
    QJsonArray loadFromFile(std::string filename);

    /**
     * @brief initSimpleTradeGoods fills simpleTradeGoods_ vector
     * @note Function tries to load items from file. If that fails, default
     * hard coded items are used for a game
     * @post Exception guarantee: nothrow
     */
    void initSimpleTradeGoods();

    /**
     * @brief jsonToSimpleTradeGoods converts QJsonObject to SimpleTradeGoods object
     * @post Exception guarantee: nothrow
     * @note If QJsonObject containing not expected values is passed, "no value"
     * SimpleTradeGoods object is created (name="", price=0)
     */
    SimpleTradeGoods jsonToSimpleTradeGoods(QJsonObject object);

    //! vector holding all SimpleTradeGoods items usable in galaxy
    std::vector<SimpleTradeGoods> simpleTradeGoods_;
};
}

#endif // ITEMSINGALAXY_HH
