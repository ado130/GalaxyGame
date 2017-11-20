#include "tradeaction.hh"

TradeAction::TradeAction(std::shared_ptr<PlayerShip> player, std::shared_ptr<Student::Planet> currentPlanet,
                         std::string action, std::shared_ptr<Common::StarSystem> currentStarSystem,
                         std::shared_ptr<Student::Question> question, std::shared_ptr<Student::Settings> settings):
    player_(player), currentPlanet_(currentPlanet), action_(action), currentStarSystem_(currentStarSystem),
    question_(question), settings_(settings)
{

}

bool TradeAction::canDo() const
{
    if(action_ == "buy")
    {
        if(player_->getInventory().size() >= MAX_PLAYER_INVENTORY &&
                currentPlanet_->getGoods().getPrice() > player_->getStatistics()->getCreditBalance())
        {
            return false;
        }
        for(auto k : player_->getInventory())
        {
            if(currentPlanet_->getGoods().getName() == k.getName() && currentPlanet_->getGoods().getPrice() == k.getPrice())
            {
                return false;
            }
        }
        return true;
    }
    else if(action_ == "sell")
    {
        for(auto k : player_->getInventory())
        {
            for(auto quest : question_->getActiveQuestions())
            {
                if(quest.first == k.getName() && quest.second.first == currentStarSystem_->getName() && quest.second.second == currentPlanet_->getName())
                {
                    return true;
                }
            }
        }
        return false;
    }
}

bool TradeAction::execute()
{
    if(action_ == "buy")
    {
        player_->addGoodsToInventory(currentPlanet_->getGoods());
        player_->getStatistics()->reduceCredits(currentPlanet_->getGoods().getPrice());
        return true;
    }
    else if(action_ == "sell")
    {
        for(auto k : player_->getInventory())
        {
            if(question_->checkQuestion(currentStarSystem_->getName(), currentPlanet_->getName(), k.getName()))
            {
                player_->removeGoodsFromInventory(k.getName());
                player_->getStatistics()->addCredits(k.getPrice() + (k.getPrice()*settings_->getCreditProfitFromSale()));
                return true;

            }
        }
    }
    else
    {
        return false;
    }
}
