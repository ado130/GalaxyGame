#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

#include <QObject>

#include "ieventhandler.hh"
#include "point.hh"

namespace Student {
class EventHandler: public QObject, public Common::IEventHandler
{
    Q_OBJECT
public:
    EventHandler(QObject* parent = 0);
    ~EventHandler();
    void shipSpawned(std::shared_ptr<Common::Ship> ship);
    void shipRemoved(std::shared_ptr<Common::Ship> ship);
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);
    void distressOn(std::shared_ptr<Common::Ship> ship);
    void distressOff(std::shared_ptr<Common::Ship> ship);
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

Q_SIGNALS:
    void shipMovement(std::shared_ptr<Common::Ship>, Common::Point from, Common::Point to);
    void shipChangedLocation(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem);
    void registerShipToUi(std::shared_ptr<Common::Ship> ship);
    void unregisterShipFromUi(std::shared_ptr<Common::Ship> ship);
    void changeShipLocationBetweenStarSystems(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem);
};
}

#endif // EVENTHANDLER_HH
