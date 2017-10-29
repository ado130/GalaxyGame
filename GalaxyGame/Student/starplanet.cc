#include "starplanet.hh"

#include <QDebug>
#include <QMap>
#include <QList>
#include <QGraphicsSceneMouseEvent>

StarPlanet::StarPlanet(Common::Point point)
{
    QMap<unsigned int, QString> planets;
    planets[0] = "earth";
    planets[1] = "jupiter";
    planets[2] = "mars";
    planets[3] = "mercury";
    planets[4] = "moon";
    planets[5] = "pluto";
    planets[6] = "venus";

    unsigned int randomPlanet = Common::randomMinMax(0, 7);
    QString planet = QString(":/images/images/planets/%1.png").arg(planets.value(randomPlanet));

    setPixmap(QPixmap(planet));
    setScale(0.3);

    setPos(point.x*100, point.y*100);
}
