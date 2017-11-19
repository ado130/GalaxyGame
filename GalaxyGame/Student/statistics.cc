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
    savedShips_++;

    if(handler_ == nullptr) return;
    handler_->statisticsUpdated();
}

unsigned Student::Statistics::getSavedShips() const
{
    return savedShips_;
}

void Student::Statistics::addLostShip()
{
    lostShips_++;

    if(handler_ == nullptr) return;
    handler_->statisticsUpdated();
}

unsigned Student::Statistics::getLostShips() const
{
    return lostShips_;
}

void Student::Statistics::addCompletedQuest()
{
    completedQuest_++;

    if(handler_ == nullptr) return;
    handler_->statisticsUpdated();
}


unsigned Student::Statistics::getCompletedQuests() const
{
    return completedQuest_;
}

void Student::Statistics::addPoints(unsigned amount)
{
    points_ += amount;

    if(handler_ == nullptr) return;
    handler_->statisticsUpdated();
}

void Student::Statistics::reducePoints(unsigned amount)
{
    if(amount > points_)
    {
        throw Common::StateException("Amount of points too low! Cannot reduce.");
    }
    else
    {
        points_ -= amount;

        if(handler_ == nullptr) return;
        handler_->statisticsUpdated();
    }
}

unsigned Student::Statistics::getPoints() const
{
    return points_;
}

void Student::Statistics::addCredits(unsigned amount)
{
    credits_ += amount;

    if(handler_ == nullptr) return;
    handler_->statisticsUpdated();
}

void Student::Statistics::reduceCredits(unsigned amount)
{

    if(amount > credits_+MAX_LOAN_ALLOWANCE)
    {
        throw Common::StateException("Amount of credits too low! Cannot reduce.");
    }
    else
    {
        credits_ -= amount;

        if(handler_ == nullptr) return;
        handler_->statisticsUpdated();
    }
}

int Student::Statistics::getCreditBalance() const
{
    return credits_;
}

void Student::Statistics::setMaxLoanAllowance(int maxLoan)
{
    MAX_LOAN_ALLOWANCE = maxLoan;
}

int Student::Statistics::getMaxLoanAllowance()
{
    return MAX_LOAN_ALLOWANCE;
}

Student::Statistics::playerStat Student::Statistics::getPlayerStat()
{
    Student::Statistics::playerStat stat;
    stat.completedQuest = completedQuest_;
    stat.credits = credits_;
    stat.lostShips = lostShips_;
    stat.points = points_;
    stat.savedShips = savedShips_;

    return stat;
}

