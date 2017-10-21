#include "starplanet.hh"

#include <QDebug>
#include <QMap>
#include <QList>
#include <QGraphicsScene>

StarPlanet::StarPlanet(QGraphicsScene *scene)
{
    scene_ = scene;

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

    bool bCollision = false;
    do
    {
        int positionX = rand() % 700;
        int positionY = rand() % 500;
        setPos(positionX, positionY);
        QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(this);
        for(int i = 0, n = colliding_Items.size(); i<n; ++i)
        {
            if(typeid (*(colliding_Items[i])) == typeid (StarPlanet))
            {
                qDebug() << "New planet - collision";
                bCollision = true;
            }
            else
            {
                bCollision = false;
            }
        }
    }while(bCollision);
}
