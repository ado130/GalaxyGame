#include "playership.hh"

#include <algorithm>

PlayerShip::PlayerShip(std::shared_ptr<Common::ShipEngine> engine,
                       std::shared_ptr<Common::StarSystem> initialLocation,
                       std::shared_ptr<Common::IEventHandler> events):
    Ship(engine, initialLocation, events)
{

    // ToDo: Settings for MAX_LOAN_ALLOWANCE
    statistics_ = Student::Statistics(5000);
}

bool PlayerShip::decideAction()
{
    return 0;
}

Student::Statistics PlayerShip::getStatistics()
{
    return statistics_;
}

void PlayerShip::removeGoodsFromInventory(std::string goods)
{
    for(auto k = inventory_.begin(); k != inventory_.end(); ++k)
    {
        if(k.base()->getName() == goods)
        {
            inventory_.erase(k);
            return;
        }
    }
}
