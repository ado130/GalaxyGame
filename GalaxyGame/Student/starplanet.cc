#include "starplanet.hh"

#include <QDebug>
#include <QMap>
#include <QList>

StarPlanet::StarPlanet()
{
    QMap<unsigned int, QString> planets;
    planets[0] = "earth";
    planets[1] = "jupiter";
    planets[2] = "mars";
    planets[3] = "mercury";
    planets[4] = "moon";
    planets[5] = "pluto";
    planets[6] = "venus";

    unsigned int randomPlanet = rand() % 7;

    QString planet = QString(":/images/images/planets/%1.png").arg(planets.value(randomPlanet));

    setPixmap(QPixmap(planet));

    setScale(0.3);

    int positionX = rand() % 800;
    int positionY = rand() % 600;
    setPos(positionX, positionY);
}
