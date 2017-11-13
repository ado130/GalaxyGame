#include "question.hh"

Student::Question::Question(std::shared_ptr<Student::Galaxy> galaxy,
                            std::shared_ptr<ItemsInGalaxy> itemsInGalaxy,
                            QObject *parent) :
    QObject(parent), galaxy_(galaxy), itemsInGalaxy_(itemsInGalaxy)
{

}

void Student::Question::generateQuestions()
{
    for(unsigned i = 0; i<MAX_QUESTIONS; ++i)
    {
        std::shared_ptr<Common::StarSystem> starSystem = galaxy_->getRandomSystem();
        Common::IGalaxy::ShipVector planetsInStarSystem = galaxy_->getPlanetsByStarSystem(galaxy_->getShipsInStarSystem(starSystem->getName()));
        while(planetsInStarSystem.size() == 0)  // in case star system does not contain any planets
        {
            starSystem = galaxy_->getRandomSystem();
            planetsInStarSystem = galaxy_->getPlanetsByStarSystem(galaxy_->getShipsInStarSystem(starSystem->getName()));
        }
        int rand = Common::randomMinMax(0, planetsInStarSystem.size()-1);
        std::shared_ptr<Common::Ship> planet = planetsInStarSystem.at(rand);
        std::string goods = itemsInGalaxy_->getRandomTradeGoods().getName();

        std::pair<std::string, std::string> location = std::make_pair(starSystem->getName(), planet->getName());
        questions_t question = std::make_pair(goods, location);
        questionList_.append(question);
    }
    activeQuestions_ = questionList_;
}

QList<questions_t> Student::Question::completedQuestions() const
{
    return completedQuestions_;
}

QList<questions_t> Student::Question::activeQuestions() const
{
    return activeQuestions_;
}

bool Student::Question::checkQuestion(std::string starSystem, std::string planet, std::string goods)
{
    for(auto k : activeQuestions_)
    {
        if(k.first == goods && k.second.first == starSystem && k.second.second == planet)
        {
            completedQuestions_.append(k);
            activeQuestions_.removeOne(k);

            if(activeQuestions_.count() == 0 && completedQuestions_.count() == MAX_QUESTIONS)
            {
                emit allQuestionsDone();
            }

            return true;
        }
    }

    return false;
}
