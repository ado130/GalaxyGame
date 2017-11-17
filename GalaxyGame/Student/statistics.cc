#include "statistics.hh"
#include "stateexception.hh"
#include "gameexception.hh"

Student::Statistics::Statistics(int maxLoanAllowance, std::shared_ptr<Student::EventHandler> handler):
    MAX_LOAN_ALLOWANCE(maxLoanAllowance), handler_(handler)
{

}

Student::Statistics::~Statistics()
{

}

void Student::Statistics::addSavedShip()
{
    savedShips++;
    handler_->statisticsUpdated();
}

unsigned Student::Statistics::getSavedShips() const
{
    return savedShips;
}

void Student::Statistics::addLostShip()
{
    lostShips++;
    handler_->statisticsUpdated();
}

unsigned Student::Statistics::getLostShips() const
{
    return lostShips;
}


void Student::Statistics::addDestroyedShip()
{
    destroyedShips++;
    handler_->statisticsUpdated();
}


unsigned Student::Statistics::getDestroyedShips() const
{
    return this->destroyedShips;
}


void Student::Statistics::addCompletedQuest()
{
    completedQuest++;
    handler_->statisticsUpdated();
}


unsigned Student::Statistics::getCompletedQuests() const
{
    return completedQuest;
}

void Student::Statistics::addPoints(unsigned amount)
{
    points += amount;
    handler_->statisticsUpdated();
}

void Student::Statistics::reducePoints(unsigned amount)
{
    if(amount > points)
    {
        throw Common::StateException("Amount of points too low! Cannot reduce.");
    }
    else
    {
        points -= amount;
        handler_->statisticsUpdated();
    }
}

unsigned Student::Statistics::getPoints() const
{
    return points;
}

void Student::Statistics::addCredits(unsigned amount)
{
    credits += amount;
    handler_->statisticsUpdated();
}

void Student::Statistics::reduceCredits(unsigned amount)
{

    if(amount > credits+MAX_LOAN_ALLOWANCE)
    {
        throw Common::StateException("Amount of credits too low! Cannot reduce.");
    }
    else
    {
        credits -= amount;
        handler_->statisticsUpdated();
    }
}

int Student::Statistics::getCreditBalance() const
{
    return credits;
}

void Student::Statistics::setMaxLoanAllowance(int maxLoan)
{
    MAX_LOAN_ALLOWANCE = maxLoan;
}

int Student::Statistics::getMaxLoanAllowance()
{
    return MAX_LOAN_ALLOWANCE;
}
