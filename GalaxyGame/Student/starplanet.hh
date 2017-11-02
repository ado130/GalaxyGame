#ifndef STARPLANET_HH
#define STARPLANET_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "starsystem.hh"

class StarPlanet : public QGraphicsPixmapItem
{
public:
    enum GOODS_TYPE {
        Oil,
        Natural_gas,
        Wood,
        Diamonds,
        Coal,
        None
    };

    StarPlanet(unsigned id, uint64_t population, Common::Point point);

    unsigned getId() const { return id_; }
    std::string getName() const { return name_; }
    GOODS_TYPE getGoods() const { return goods_; }
    Common::Point getCoordinates() const { return coordinates_; }
    uint64_t getPopulation() const { return population_; }
    Common::StarSystem::ECONOMY_TYPE getEconomy() const { return economy_; }
private:
    std::string name_;
    Common::StarSystem::ECONOMY_TYPE economy_;
    unsigned id_;
    uint64_t population_;
    Common::Point coordinates_;
    GOODS_TYPE goods_;
};

#endif // STARPLANET_HH
