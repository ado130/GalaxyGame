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

class TradeAction : public Common::IAction
{
public:
    TradeAction(std::shared_ptr<PlayerShip> player, std::shared_ptr<Student::Planet> currentPlanet,
                std::string action, std::shared_ptr<Common::StarSystem> currentStarSystem,
                std::shared_ptr<Student::Question> question, std::shared_ptr<Student::Settings> settings);

    // IAction interface
public:
    bool canDo() const;
    bool execute();
private:
    std::shared_ptr<PlayerShip> player_;
    std::shared_ptr<Student::Planet> currentPlanet_;
    std::string action_;
    std::shared_ptr<Common::StarSystem> currentStarSystem_;
    std::shared_ptr<Student::Question> question_;
    std::shared_ptr<Student::Settings> settings_;
};

#endif // TRADEACTION_HH
