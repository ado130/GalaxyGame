#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

#include <QObject>

#include "ieventhandler.hh"
#include "point.hh"

namespace Student {

/**
 * @class Common::IEventHandler
 * @brief Event handler acts as an intermediary between objects that receives events and
 * the objects that are interested in those events. Objects spawn events by calling functions of
 * the event handler. See more details in the sequence diagrams within the course assignment.
 */
class EventHandler: public QObject, public Common::IEventHandler
{
    Q_OBJECT
public:
    EventHandler(QObject* parent = 0);
    ~EventHandler();

    /**
     * @brief A new ship has been created in the galaxy.
     * @param ship The created ship
     * @post Exception guarantee: nothrow
     */
    void shipSpawned(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief A ship has been removed from the galaxy.
     * @param ship The removed ship
     * @post Exception guarantee: nothrow
     */
    void shipRemoved(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief A ship has moved to a star system, or moved away from a star system.
     * @param ship The ship, which relocated
     * @param starSystem The previous system where the ship was located. Can be nullptr.
     * @post Exception guarantee: nothrow
     */
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @brief A ship moved from one point to another.
     * @param ship The ship, which moved
     * @param origin The point, from which the ship moved
     * @param target The point, to which the ship moved
     * @post Exception guarantee: nothrow
     */
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);

    /**
     * @brief An action executed by a ship caused an exception, and thus it was cancelled.
     * @param ship The ship that caused the exception.
     * @param msg Description of the exception.
     * @post Exception guarantee: nothrow
     */
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);

    /**
     * @brief A ship has switched on distress call.
     * @param ship The ship, which switched on the distress call
     * @post Exception guarantee: nothrow
     */
    void distressOn(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief A ship has switched off distress call.
     * @param ship The ship, which switched off the distress call
     * @post Exception guarantee: nothrow
     */
    void distressOff(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief A ship has been abandoned.
     * @param ship The ship, which has been abandoned
     * @post Exception guarantee: nothrow
     */
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief Statistics have been changed.
     * @post Exception guarantee: nothrow
     * @post statisticsNeedUpdate signal is emited
     */
    virtual void statisticsUpdated();

Q_SIGNALS:
    //! signal emited when ship moved between Star Systems
    void shipMovement(std::shared_ptr<Common::Ship>, Common::Point from, Common::Point to);

    //! signal emited when ship reached Star System
    void shipChangedLocation(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem);

    //! signal emited when new ship is spawned
    void registerShipToUi(std::shared_ptr<Common::Ship> ship);

    //! signal emited when ship is destroyed
    void unregisterShipFromUi(std::shared_ptr<Common::Ship> ship);

    //! signal emited when ship is in distress
    void shipCallForHelp(std::shared_ptr<Common::Ship> ship);

    //! signal emited when ship is out of distress
    void shipWasSaved(std::shared_ptr<Common::Ship> ship);

    //! signal emited when ship was not save in time
    void shipWasAbandoned(std::shared_ptr<Common::Ship> ship);

    //! signal emited when Statistics object has been changed
    void statisticsNeedUpdate(bool update);

    //! signal emited when GameException in ship execution happens
    void exceptionInShipExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);
};
}

#endif // EVENTHANDLER_HH
