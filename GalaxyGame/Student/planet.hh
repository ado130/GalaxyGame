#ifndef PLANET_HH
#define PLANET_HH

#include "planetcoredrive.hh"
#include "ship.hh"


namespace Student {
class Planet : public Common::Ship
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

    typedef std::vector<std::shared_ptr<Planet> > StarPlanetVector;

    Planet(std::shared_ptr<PlanetCoreDrive> engine,
           std::shared_ptr<Common::StarSystem> starSystem,
           std::shared_ptr<Common::IEventHandler> events);
    ~Planet();

    unsigned getId() const { return id_; }
    GOODS_TYPE getGoods() const { return goods_; }
    std::shared_ptr<Common::StarSystem> getLocation() { return location_; }
    std::string getName() const { return name_; }
    void setName(std::string name) { name_ = name; }
    void setLocation(std::shared_ptr<Common::StarSystem> newLocation) { location_ = newLocation; }

    void executeAction() {}

    void abandonShip() {}

    bool isAbandoned() { return false; }

    bool decideAction() { return false; }

    std::shared_ptr<Common::IAction> getAction() const;

private:
    unsigned id_;
    GOODS_TYPE goods_;

//    NOTE:
//    If we want to have planet population, we have to compute it ---> if sum
//    of all populations from all planets from certain starsystem == starsystem.getPopulaiton();
//    uint64_t population_;

//    NOTE:
//    StarSystem has Economy Type --> planets in starsystem should have the same economy type (or most
//    of them should) as the starsystem. Better is to have only GOODS_TYPE, which could correspond with economy type (e.g.
//    starsystem has agriculture economy --> one planet is starsystem offers carrots, one weed etc..)
//    Common::StarSystem::ECONOMY_TYPE economy_;
};
}
#endif // PLANET_HH
