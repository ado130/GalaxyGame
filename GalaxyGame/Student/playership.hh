#ifndef PLAYERSHIP_HH
#define PLAYERSHIP_HH

#include "ship.hh"
#include "statistics.hh"
#include "simpletradegoods.hh"

#define MAX_PLAYER_INVENTORY 5

/**
 * @brief PlayerShip object is user controlled ship.
 * PlayerShip can save ships, travel among StarSystems,
 * trade with Planets and complete Questions.
 */
class PlayerShip : public Common::Ship
{
public:
    /**
     * @brief Constructor
     * @param engine ship engine
     * @param initialLocation initial StarSystem
     * @param events EventHandler
     * @param statistics Statistics object
     */
    PlayerShip(std::shared_ptr<Common::ShipEngine> engine = 0,
               std::shared_ptr<Common::StarSystem> initialLocation = 0,
               std::shared_ptr<Common::IEventHandler> events = 0, Student::Statistics *statistics = nullptr);

    /**
     * @brief getStatistics
     * @return player's Statistics
     * @post Exception guarantee: nothrow
     */
    Student::Statistics* getStatistics();

    /**
     * @brief getInventory
     * @return SimpleTradeGoods vector of player's items in inventory
     * @post Exception guarantee: nothrow
     */
    std::vector<SimpleTradeGoods> getInventory() const {return inventory_;}

    /**
     * @brief addGoodsToInventory
     * @param goods SimpleTradeGoods item
     * @post Exception guarantee: nothrow
     * @post goods item is added to player's inventory
     */
    void addGoodsToInventory(SimpleTradeGoods goods) {inventory_.push_back(goods);}

    /**
     * @brief removeGoodsFromInventory
     * @param goods SimpleTradeGoods item
     * @post Exception guarantee: nothrow
     * @post goods item is removed from player's inventory
     */
    void removeGoodsFromInventory(std::string goods);

    /**
     * @brief decideAction
     * @note method inherited from ship interface, not used
     * @post Exception guarantee: nothrow
     */
    bool decideAction();    // ship interface
private:
    //! Statistics object counting player's statistics
    Student::Statistics *statistics_;

    //! SimpleTradeGoods vector representing player's inventory
    std::vector<SimpleTradeGoods> inventory_;
};

#endif // PLAYERSHIP_HH
