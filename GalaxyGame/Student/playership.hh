#ifndef PLAYERSHIP_HH
#define PLAYERSHIP_HH

#include "ship.hh"
#include "statistics.hh"
#include "simpletradegoods.hh"

#define MAX_PLAYER_INVENTORY 5

class PlayerShip : public Common::Ship
{
public:
    PlayerShip(std::shared_ptr<Common::ShipEngine> engine = 0,
               std::shared_ptr<Common::StarSystem> initialLocation = 0,
               std::shared_ptr<Common::IEventHandler> events = 0);
    Student::Statistics getStatistics();

    std::vector<SimpleTradeGoods> getInventory() const {return inventory_;}
    void addGoodsToInventory(SimpleTradeGoods goods) {inventory_.push_back(goods);}
    void removeGoodsFromInventory(std::string goods);

    bool decideAction();    // ship interface
private:
    Student::Statistics statistics_;
    std::vector<SimpleTradeGoods> inventory_;
};

#endif // PLAYERSHIP_HH
