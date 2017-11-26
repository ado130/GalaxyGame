#include "playership.hh"

#include <algorithm>
#include <cassert>

Student::PlayerShip::PlayerShip(std::shared_ptr<Common::ShipEngine> engine,
                       std::shared_ptr<Common::StarSystem> initialLocation,
                       std::shared_ptr<Common::IEventHandler> events,
                       Student::Statistics *statistics):
    Ship(engine, initialLocation, events), statistics_(statistics)
{

}

bool Student::PlayerShip::decideAction()
{
    return 0;
}

Student::Statistics *Student::PlayerShip::getStatistics()
{
    assert(statistics_);

    return statistics_;
}

void Student::PlayerShip::removeGoodsFromInventory(std::string goods)
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
