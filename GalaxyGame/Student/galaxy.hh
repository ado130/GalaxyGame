#ifndef GALAXY_HH
#define GALAXY_HH

#include "igalaxy.hh"

namespace Student {

/**
 * @brief Interface for Galaxy
 *
 * @invariant Starsystems have unique name, id and location. Ship objects in a galaxy must be unique.
 */
class Galaxy : public Common::IGalaxy, public std::enable_shared_from_this<Galaxy>
{
public:
    Galaxy();
    ~Galaxy();
    //IGalaxy

    /**
     * @brief addShip Adds a new ship to the galaxy
     * @param ship Ship to be added to the galaxy.
     * @post Ship is added to the galaxy.
     * @exception StateException If the galaxy contains the ship object already.
     * @post Exception guarantee: strong
     */
    virtual void addShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief removeShip removes a ship from the galaxy.
     * @param ship Ship to be removed
     * @post Ship is removed from the galaxy
     * @exception ObjectNotFoundException, if the ship does not exist
     * @post Exception guarantee: strong
     */
    virtual void removeShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief addStarSystem adds a new star system to the galaxy
     * @param system Star system to be added to the galaxy
     * @post Star system is added to the galaxy
     * @exception StateException, if a star system with the same name or id or location already exists in the galaxy
     * @post Exception guarantee: strong
     */
    virtual void addStarSystem(std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @brief getShips
     * @return Shared pointer to the vector containing ships in the galaxy. Empty vector, if there are no ships
     * @post Exception guarantee: nothrow
     */
    virtual std::shared_ptr<ShipVector> getShips();

    /**
     * @brief getSystemsInRange
     * @param origin Star system of interest
     * @param range Distance in light years
     * @exception Throws an ObjectNotFoundException, if the star system is not in the galaxy
     * @return Star systems that are within within the distance from the system of interest. Empty vector, if there are no such star systems
     * @post Exception guarantee: strong
     */
    virtual Common::StarSystem::StarSystemVector getSystemsInRange
    (std::shared_ptr<Common::StarSystem> origin, int range);

    /**
     * @brief getRandomSystem returns a random star system
     * @return A random star system from the set of star systems added to the galaxy
     * @exception ObjectNotFoundException, if the galaxy has no star systems
     * @post Exception guarantee: strong
     */
    virtual std::shared_ptr<Common::StarSystem> getRandomSystem();

    /**
     * @brief getShipsInStarSystem
     * @param name Name of the star system
     * @return Returns vector of all ships in the star system. Empty vector, if there are no ships in the star system.
     * @exception ObjectNotFoundException, if the star system with given name does not exist
     * @post Exception guarantee: strong
     */
    ShipVector getShipsInStarSystem(std::string name);

    /**
     * @brief getStarSystemByName gets the instance of a star system by name
     * @param name Name of the star system
     * @return Shared pointer to the object of the star system
     * @exception ObjectNotFoundException, if the star system with given name does not exist
     * @post Exception guarantee: strong
     */
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);

    /**
     * @brief getStarSystemById gets an instance of the star system by id
     * @param id Id of the star system
     * @return Shared pointer to the object of the star system
     * @exception ObjectNotFoundException, if the star system with given id does not exist
     * @post Exception guarantee: strong
     */
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);

    /**
     * @brief getStarSystemVector
     * @return StarSystemVector of all star systems in galaxy
     */
    Common::StarSystem::StarSystemVector getStarSystemVector() const {return starSystemsInGalaxy_;}

    /**
     * @brief removeShips removes all ships in galaxy
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
