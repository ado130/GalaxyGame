#ifndef ITEMSINGALAXY_HH
#define ITEMSINGALAXY_HH

#include "iitemingalaxy.hh"
#include "simpletradegoods.hh"

#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <memory>

class ItemsInGalaxy
{
public:
    ItemsInGalaxy();

    std::vector<SimpleTradeGoods> getSimpleTradeGoods();
    SimpleTradeGoods getRandomTradeGoods();

private:
    QJsonArray loadFromFile(std::string filename);
    void initSimpleTradeGoods();
    SimpleTradeGoods jsonToSimpleTradeGoods(QJsonObject object);

    std::vector<SimpleTradeGoods> simpleTradeGoods_;
};

#endif // ITEMSINGALAXY_HH
