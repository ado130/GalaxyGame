#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

#include <QObject>

#include "ieventhandler.hh"
#include "point.hh"

namespace Student {

/**
 * @copydoc IEventHandler;
 */
class EventHandler: public QObject, public Common::IEventHandler
{
    Q_OBJECT
public:
    EventHandler(QObject* parent = 0);
    ~EventHandler();

    /**
     * @copydoc IEventHandler::shipSpawned();
     * @post registerShipToUi signal is emited
     */
    void shipSpawned(std::shared_ptr<Common::Ship> ship);
    /**
     * @copydoc IEventHandler::shipRemoved();
     * @post registerShipToUi signal is emited
     */
    void shipRemoved(std::shared_ptr<Common::Ship> ship);
    /**
     * @copydoc IEventHandler::shipRelocated();
     * @post shipChangedLocation signal is emited if all data needed are present
     */
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);
    /**
     * @copydoc IEventHandler::shipMoved();
     * @post shipMovement signal is emited
     */
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);
    /**
     * @copydoc IEventHandler::exceptionInExecution();
     * @post exceptionInShipExecution signal is emited
     */
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);

    /**
     * @copydoc IEventHandler::distressOn();
     * @post shipCallForHelp signal is emited
     */
    void distressOn(std::shared_ptr<Common::Ship> ship);

    /**
     * @copydoc IEventHandler::distressOff();
     * @post shipWasSaved signal is emited
     */
    void distressOff(std::shared_ptr<Common::Ship> ship);

    /**
     * @copydoc IEventHandler::shipAbandoned();
     * @post shipWasAbandoned signal is emited
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
