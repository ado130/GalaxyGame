#ifndef PLANET_HH
#define PLANET_HH

#include "planetcoredrive.hh"
#include "simpletradegoods.hh"


namespace Student {
/**
 * @brief Planet is a type of ship with immobile PlanetCoreDrive engine.
 * Every planet sells one type of SimpleTradeGoods.
 */
class Planet : public Common::Ship
{
public:
    //! vector structure for Planets defined
    typedef std::vector<std::shared_ptr<Planet> > StarPlanetVector;

    /**
     * @brief Constructor
     * @param engine PlanetCoreDrive ship engine
     * @param starSystem Star System where Planet is located
     * @param events EventHandler object
     * @param simpleTradeGoods goods which planet sells
     */
    Planet(std::shared_ptr<PlanetCoreDrive> engine,
           std::shared_ptr<Common::StarSystem> starSystem,
           std::shared_ptr<Common::IEventHandler> events,
           SimpleTradeGoods simpleTradeGoods);


    /**
     * @brief Destructor.
     */
    ~Planet();


    /**
     * @brief getId
     * @return usigned id of Planet
     * @post Exception guarantee: nothrow
     */
    unsigned getId() const { return id_; }


    /**
     * @brief getGoods
     * @return object of SimpleTradeGoods sold by Planet
     * @post Exception guarantee: nothrow
     */
    SimpleTradeGoods getGoods() const { return simpleTradeGoods_; }

    /**
     * @copydoc Common::Ship.executeAction();
     * @note Planet doesn't have any actions at the moment.
     * @post Exception guarantee: nothrow
     */
    void executeAction() {}

    /**
     * @copydoc Common::Ship.abandonShip();
     * @note Planet cannot be abandoned at the moment.
     * @post Exception guarantee: nothrow
     */
    void abandonShip() {}

    /**
     * @copydoc Common::Ship.isAbandoned();
     * @return False, because Planet cannot abandoned at the moment.
     * @note Planet cannot be abandoned at the moment.
     * @post Exception guarantee: nothrow
     */
    bool isAbandoned() { return false; }

    /**
     * @copydoc Common::Ship.decideAction();
     * @return False, because Planet does not have any actions at the moment.
     * @note Planet doesn't have any actions at the moment.
     * @post Exception guarantee: nothrow
     */
    bool decideAction() { return false; }

    /**
     * @copydoc Common::Ship.getAction();
     * @return current action
     * @note Planet doesn't have any actions at the moment.
     * @pre currentAction_ object is asociated with this object
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Common::IAction> getAction() const;

private:
    //! Planet's id
    unsigned id_;
    //! simpleTradeGoods_ are goods sold by this Planet
    SimpleTradeGoods simpleTradeGoods_;
};
}
#endif // PLANET_HH
