#ifndef STARPLANET_HH
#define STARPLANET_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "starsystem.hh"

class StarPlanet : public Common::StarSystem, public QGraphicsPixmapItem
{
public:
    StarPlanet(std::string name, ECONOMY_TYPE economy, unsigned id,
               uint64_t population, Common::Point location);
private:

};

#endif // STARPLANET_HH
