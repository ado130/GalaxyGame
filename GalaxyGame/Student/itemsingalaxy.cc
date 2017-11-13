#include "itemsingalaxy.hh"
#include "utility.hh"
#include "ioexception.hh"
#include "formatexception.hh"

#include <QFile>;
#include <QJsonDocument>

QString const ASSET_FOLDER("Assets/");

ItemsInGalaxy::ItemsInGalaxy()
{

}

void ItemsInGalaxy::initSimpleTradeGoods(){
    QJsonArray jsonArr = loadFromFile("simpleTradeGoods.json");
    for(auto object : jsonArr){
        simpleTradeGoods_.push_back(jsonToSimpleTradeGoods(object.toObject()));
    }
}

std::vector<SimpleTradeGoods> ItemsInGalaxy::getSimpleTradeGoods()
{
    if(simpleTradeGoods_.empty()){
        initSimpleTradeGoods();
    }
    return simpleTradeGoods_;
}

SimpleTradeGoods ItemsInGalaxy::getRandomTradeGoods()
{
    if(simpleTradeGoods_.empty()){
        initSimpleTradeGoods();
    }
    int rand = Common::randomMinMax(0, simpleTradeGoods_.size()-1);
    return simpleTradeGoods_.at(rand);
}

QJsonArray ItemsInGalaxy::loadFromFile(std::string filename)
{
    QFile file (ASSET_FOLDER + QString::fromStdString(filename));
    if (!file.open(QFile::ReadOnly))
    {
        throw Common::IoException("Could not read file " + filename);
    }
    QJsonDocument systemJSON = QJsonDocument::fromJson(file.readAll());

    if (systemJSON.isNull()) {
        throw Common::FormatException("JSON parsing failed for input file " + filename);
    }
    else {
        return systemJSON.array();
    }
}

SimpleTradeGoods ItemsInGalaxy::jsonToSimpleTradeGoods(QJsonObject object)
{
    return SimpleTradeGoods( (object.value("name")).toString().toStdString(),
                                         (object.value("price")).toInt()
                                         );
}
