#ifndef TRADEACTION_HH
#define TRADEACTION_HH

#include "iaction.hh"
#include "playership.hh"
#include "planet.hh"
#include "question.hh"
#include "starsystem.hh"
#include "settings.hh"

#include <memory>
#include <string>

/**
 * @brief The TradeAction class is used when PlayerShip invokes trade with Planet
 */
class TradeAction : public Common::IAction
{
public:
    /**
     * @brief TradeAction
     * @param player PlayerShip invoking trade
     * @param currentPlanet Planet which whom player wants to trade
     * @param action action indicates whether player wants to "sell" or "buy"
     * @param currentStarSystem current location of player and planet
     * @param question Question object checking fullfilment of questions
     * @param settings current game settings
     */
    TradeAction(std::shared_ptr<PlayerShip> player, std::shared_ptr<Student::Planet> currentPlanet,
                std::string action, std::shared_ptr<Common::StarSystem> currentStarSystem,
                std::shared_ptr<Student::Question> question, std::shared_ptr<Student::Settings> settings);

    // IAction interface
public:
    /**
     * @brief canDo
     * @return true when action can be done, else false
     * @post Exception guarantee: nothrow
     */
    bool canDo() const;

    /**
     * @brief execute trade action
     * @post if action == "sell", goods from player's inventory is erased and
     * credits added to player's account. Else if action == "buy", goods is added
     * to player's inventory and credits reduced
     * @return true if trade is sucessfully completed, else false
     */
    bool execute();
private:
    //! PlayerShip invoking trade
    std::shared_ptr<PlayerShip> player_;

    //! Planet which whom player wants to trade
    std::shared_ptr<Student::Planet> currentPlanet_;

    //! action indicates whether player wants to "sell" or "buy"
    std::string action_;

    //! current location of player and planet
    std::shared_ptr<Common::StarSystem> currentStarSystem_;

    //! Question object checking fullfilment of questions
    std::shared_ptr<Student::Question> question_;

    //! current game settings
    std::shared_ptr<Student::Settings> settings_;
};

#endif // TRADEACTION_HH
