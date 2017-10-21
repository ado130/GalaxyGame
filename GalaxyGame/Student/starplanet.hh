#ifndef STARPLANET_HH
#define STARPLANET_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "starsystem.hh"

class StarPlanet : public QGraphicsPixmapItem
{
public:
    StarPlanet(QGraphicsScene *scene);

private:
    QGraphicsScene *scene_;
};

#endif // STARPLANET_HH
