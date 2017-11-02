#include "starplanet.hh"

#include <QDebug>
#include <QMap>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <string>

StarPlanet::StarPlanet(unsigned id, uint64_t population, Common::Point point) :
    id_(id), population_(population), coordinates_(point)
{
    // ToDo: load planets from file, store in separate object
    std::vector<std::string> planets =  {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};
    int randomPlanetIndex = Common::randomMinMax(0, planets.size()-1);
    QString randomPlanetName = QString::fromStdString(planets.at(randomPlanetIndex));
    QString planet = QString(":/images/images/planets/%1.png").arg(randomPlanetName.toLower());

    name_ = planets.at(randomPlanetIndex);
    goods_ = static_cast<GOODS_TYPE>(Common::randomMinMax(0, 5));
    economy_ = static_cast<Common::StarSystem::ECONOMY_TYPE>(Common::randomMinMax(0, 10));;

    setPixmap(QPixmap(planet));
    setScale(0.3);

    int posX = Common::randomMinMax(-500, 500);
    int posY = Common::randomMinMax(-500, 500);

    coordinates_ = Common::Point(posX, posY);

    setPos(posX, posY);
}
