#ifndef IEVENTHANDLER_HH
#define IEVENTHANDLER_HH

#include <string>
#include <memory>

#ifdef English_dox
/**
 * @file
 * @brief Defines the interface for handling events
 */
#endif

namespace Common {

#ifdef English_dox
/**
 * @class Common::IEventHandler
 * @brief Event handler acts as an intermediary between objects that receives events and the objects that are interested in those events.
 * EventHander is used as a parameter in the construction of those objects which need to notify others about events/happenings.
 * Vessels and some action classes are an example of this.
 *
 * These events can be used to update the user interface for example.
 *
 */
#endif

#ifdef English_dox
/**
 * Predefinition of necessary classes.
 */
#endif
class Ship;
class StarSystem;
struct Point;

class IEventHandler
{
public:
#ifdef English_dox
    /**
      * @brief Default constructor of interface (exists for the sake of documentation)
      */
#endif
    IEventHandler() = default;

 #ifdef English_dox
    /**
     * @brief Interface has a default constructor (exists as base class needs to have a virtual destructor)
     */
#endif
    virtual ~IEventHandler() = default;

#ifdef English_dox
    /**
     * @brief shipSpawned A new ship has been created in the galaxy.
     * @param ship Created ship
     */
#endif
    virtual void shipSpawned(std::shared_ptr<Ship> ship) = 0;

#ifdef English_dox
    /**
     * @brief shipRemoved A ship has been removed from the galaxy.
     * @param ship Removed ship
     */
#endif
    virtual void shipRemoved (std::shared_ptr<Ship> ship) = 0 ;

#ifdef English_dox
    /**
     * @brief shipMoved A ship moved from one point to another
     * @param ship Ship, which moved
     * @param origin point, from which the ship moved
     * @param target point, to which the ship moved
     */
#endif
    virtual void shipMoved(std::shared_ptr<Ship> ship, Point origin, Point target) = 0 ;

#ifdef English_dox
    /**
     * @brief shipRelocated Ship moved to the provided Star system.
     * @param ship Ship, which relocated
     * @param starSystem nullptr, when a ship leaves from the Star system. Destination Star system, if the ship reached one.
     */
#endif
    virtual void shipRelocated(std::shared_ptr<Ship> ship, std::shared_ptr<StarSystem> starSystem) = 0;

#ifdef English_dox
    /**
     * @brief exceptionInExecution A function executed by the ship caused an exception to be thrown, which has the reason added as a string
     */
#endif
    virtual void exceptionInExecution(std::shared_ptr<Ship>, std::string const&) = 0;

#ifdef English_dox
    /**
     * @brief distressOn A ship has made a distress call.
     * @param ship Ship, which made the distress call
     */
#endif
    virtual void distressOn(std::shared_ptr<Ship> ship) = 0 ;

#ifdef English_dox
    /**
     * @brief distressOff A ship has removed the distress call.
     * @param ship Ship, which removed the distress call
     */
#endif
    virtual void distressOff(std::shared_ptr<Ship> ship) = 0;

#ifdef English_dox
    /**
     * @brief shipAbandoned A ship has been abandoned.
     * @param ship Ship, which has been abandoned
     */
#endif
    virtual void shipAbandoned(std::shared_ptr<Ship> ship) = 0;
};

}

#endif // IEVENTHANDLER_HH
