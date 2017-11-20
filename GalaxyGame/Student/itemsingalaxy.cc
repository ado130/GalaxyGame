#include "itemsingalaxy.hh"
#include "utility.hh"
#include "ioexception.hh"
#include "formatexception.hh"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

QString const ASSET_FOLDER("Assets/");

ItemsInGalaxy::ItemsInGalaxy()
{

}

void ItemsInGalaxy::initSimpleTradeGoods()
{
    QJsonArray jsonArr;
    try
    {
        jsonArr = loadFromFile("simpleTradeGoods.json");
    }
    catch(...)
    {
        auto item1 = QJsonObject(
        {
            qMakePair(QString("name"), QJsonValue("Oil")),
            qMakePair(QString("price"), QJsonValue(7))
        });

        auto item2 = QJsonObject(
        {
            qMakePair(QString("name"), QJsonValue("Wood")),
            qMakePair(QString("price"), QJsonValue(3))
        });

        auto item3 = QJsonObject(
        {
            qMakePair(QString("name"), QJsonValue("Diamonds")),
            qMakePair(QString("price"), QJsonValue(10))
        });
            jsonArr.push_back(QJsonValue(item1));
            jsonArr.push_back(QJsonValue(item2));
            jsonArr.push_back(QJsonValue(item3));
    }

    for(auto object : jsonArr)
    {
        simpleTradeGoods_.push_back(jsonToSimpleTradeGoods(object.toObject()));
    }
}

std::vector<SimpleTradeGoods> ItemsInGalaxy::getSimpleTradeGoods()
{
    if(simpleTradeGoods_.empty())
    {
        initSimpleTradeGoods();
    }
    return simpleTradeGoods_;
}

SimpleTradeGoods ItemsInGalaxy::getRandomTradeGoods()
{
    if(simpleTradeGoods_.empty())
    {
        initSimpleTradeGoods();
    }
    int rand = Common::randomMinMax(0, simpleTradeGoods_.size()-1);
    return simpleTradeGoods_.at(rand);
}

QJsonArray ItemsInGalaxy::loadFromFile(std::string filename)
{
    QFile file (ASSET_FOLDER + QString::fromStdString(filename));
    if(!file.open(QFile::ReadOnly))
    {
        throw Common::IoException("Could not read file " + filename);
    }
    QJsonDocument systemJSON = QJsonDocument::fromJson(file.readAll());

    if(systemJSON.isNull())
    {
        throw Common::FormatException("JSON parsing failed for input file " + filename);
    }
    else
    {
        return systemJSON.array();
    }
}

SimpleTradeGoods ItemsInGalaxy::jsonToSimpleTradeGoods(QJsonObject object)
{
    return SimpleTradeGoods( object.value("name").toString().toStdString(), object.value("price").toInt());
}
