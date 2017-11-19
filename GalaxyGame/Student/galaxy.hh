#ifndef GALAXY_HH
#define GALAXY_HH

#include "igalaxy.hh"

namespace Student {

class Galaxy : public Common::IGalaxy, public std::enable_shared_from_this<Galaxy>
{
public:
    Galaxy();
    ~Galaxy();
    //IGalaxy
    virtual void addShip(std::shared_ptr<Common::Ship> ship);
    virtual void removeShip(std::shared_ptr<Common::Ship> ship);
    virtual void addStarSystem(std::shared_ptr<Common::StarSystem> starSystem);

    virtual std::shared_ptr<ShipVector> getShips();

    virtual Common::StarSystem::StarSystemVector getSystemsInRange
    (std::shared_ptr<Common::StarSystem> origin, int range);
    virtual std::shared_ptr<Common::StarSystem> getRandomSystem();

    ShipVector getShipsInStarSystem(std::string name);
    std::vector<std::string> getSystemNames();
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);
    Common::StarSystem::StarSystemVector getStarSystemVector() const {return starSystemsInGalaxy_;}

    void removeShips() { shipsInGalaxy_.clear(); }
private:
    ShipVector shipsInGalaxy_;
    Common::StarSystem::StarSystemVector starSystemsInGalaxy_;
};
}//Student

#endif // GALAXY_HH
