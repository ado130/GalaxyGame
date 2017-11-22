#ifndef GALAXY_HH
#define GALAXY_HH

#include "igalaxy.hh"

namespace Student {

/**
 * @copydoc Common::IGalaxy
 */
class Galaxy : public Common::IGalaxy, public std::enable_shared_from_this<Galaxy>
{
public:
    Galaxy();
    ~Galaxy();
    //IGalaxy

    /**
     * @copydoc Common::IGalaxy.addShip();
     */
    virtual void addShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @copydoc Common::IGalaxy.removeShip();
     */
    virtual void removeShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @copydoc Common::IGalaxy.addStarSystem();
     */
    virtual void addStarSystem(std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @copydoc Common::IGalaxy.getShips()
     */
    virtual std::shared_ptr<ShipVector> getShips();

    /**
     * @copydoc Common::IGalaxy.getSystemsInRange()
     */
    virtual Common::StarSystem::StarSystemVector getSystemsInRange
    (std::shared_ptr<Common::StarSystem> origin, int range);

    /**
     * @copydoc Common::IGalaxy.getRandomSystem()
     */
    virtual std::shared_ptr<Common::StarSystem> getRandomSystem();

    /**
     * @copydoc Common::IGalaxy.getShipsInStarSystem()
     */
    ShipVector getShipsInStarSystem(std::string name);

    /**
     * @copydoc Common::IGalaxy.getStarSystemByName()
     */
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);

    /**
     * @copydoc Common::IGalaxy.getStarSystemById()
     */
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);

    /**
     * @copydoc Common::IGalaxy.getStarSystemVector()
     */
    Common::StarSystem::StarSystemVector getStarSystemVector() const {return starSystemsInGalaxy_;}

    /**
     * @copydoc Common::IGalaxy.removeShips();
     */
    void removeShips() { shipsInGalaxy_.clear(); }
private:
    //! All ships in galaxy
    ShipVector shipsInGalaxy_;

    //! All star systems in galaxy
    Common::StarSystem::StarSystemVector starSystemsInGalaxy_;
};
}//Student

#endif // GALAXY_HH
