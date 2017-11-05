#ifndef PLAYERSHIP_HH
#define PLAYERSHIP_HH

#include "ship.hh"
#include "statistics.hh"

class PlayerShip : public Common::Ship
{
public:
    PlayerShip(std::shared_ptr<Common::ShipEngine> engine = 0,
               std::shared_ptr<Common::StarSystem> initialLocation = 0,
               std::shared_ptr<Common::IEventHandler> events = 0);
    Student::Statistics getStatistics();
private:
    Student::Statistics statistics_;

    // Ship interface
public:
    bool decideAction();
};

#endif // PLAYERSHIP_HH
