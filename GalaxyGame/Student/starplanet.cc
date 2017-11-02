#include "starplanet.hh"

#include <QDebug>
#include <QMap>
#include <QList>
#include <QGraphicsSceneMouseEvent>

StarPlanet::StarPlanet(unsigned id, uint64_t population, Common::Point point) :
    id_(id), population_(population), coordinates_(point)
{
    const char* planets[] =  {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};

    unsigned int randomPlanet = Common::randomMinMax(0, 7);
    QString planet = QString(":/images/images/planets/%1.png").arg(QString(planets[randomPlanet]).toLower());

    name_ = planets[randomPlanet];
    goods_ = static_cast<GOODS_TYPE>(Common::randomMinMax(0, 6));
    economy_ = static_cast<Common::StarSystem::ECONOMY_TYPE>(Common::randomMinMax(0, 11));;

    setPixmap(QPixmap(planet));
    setScale(0.3);

    int posX = Common::randomMinMax(-500, 500);
    int posY = Common::randomMinMax(-500, 500);

    coordinates_ = Common::Point(posX, posY);

    setPos(posX, posY);
}












