#ifndef GALAXY_HH
#define GALAXY_HH

#include <QObject>

#include "igalaxy.hh"
#include "ship.hh"
#include "starsystem.hh"
#include "ieventhandler.hh"

namespace Student {

class Galaxy : public QObject, public Common::IGalaxy, public std::enable_shared_from_this<Galaxy>
{
    Q_OBJECT
public:
    Galaxy(QObject* parent = 0);
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

Q_SIGNALS:
    void shipEvent(std::shared_ptr<Common::Ship> ship, bool newShip);

private:
    ShipVector shipsInGalaxy_;
    Common::StarSystem::StarSystemVector starSystemsInGalaxy_;

    //friend bool operator== ( const Nick &n1, const Nick &n2);

};
}//Student

#endif // GALAXY_HH
