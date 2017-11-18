#include "statistics.hh"
#include "stateexception.hh"
#include "gameexception.hh"

#include <QDataStream>
#include <QFile>


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
    handler_->statisticsUpdated();
}

unsigned Student::Statistics::getSavedShips() const
{
    return savedShips_;
}

void Student::Statistics::addLostShip()
{
    lostShips_++;
    handler_->statisticsUpdated();
}

unsigned Student::Statistics::getLostShips() const
{
    return lostShips_;
}


void Student::Statistics::addDestroyedShip()
{
    destroyedShips_++;
    handler_->statisticsUpdated();
}


unsigned Student::Statistics::getDestroyedShips() const
{
    return this->destroyedShips_;
}


void Student::Statistics::addCompletedQuest()
{
    completedQuest_++;
    handler_->statisticsUpdated();
}


unsigned Student::Statistics::getCompletedQuests() const
{
    return completedQuest_;
}

void Student::Statistics::addPoints(unsigned amount)
{
    points_ += amount;
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

QMap<QString, Student::Statistics::playerStat> Student::Statistics::getTotalStat() const
{
    return totalStat_;
}

void Student::Statistics::loadSettings()
{
    QFile file("stats.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> totalStat_;
}

void Student::Statistics::saveSettings(QString name)
{
    playerStat playerStat;
    playerStat.completedQuest = completedQuest_;
    playerStat.credits = credits_;
    playerStat.destroyedShips = destroyedShips_;
    playerStat.lostShips = lostShips_;
    playerStat.points = points_;
    playerStat.savedShips = savedShips_;

    totalStat_[name] = playerStat;

    QFile file("stats.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << totalStat_;
}

QDataStream &operator<<(QDataStream &out, const Student::Statistics::playerStat &playerStat)
{
    out << playerStat.completedQuest << playerStat.credits << playerStat.destroyedShips << playerStat.lostShips << playerStat.points << playerStat.savedShips;
    return out;
}

QDataStream &operator>>(QDataStream &in, Student::Statistics::playerStat &playerStat)
{
    in >> playerStat.completedQuest >> playerStat.credits >> playerStat.destroyedShips >> playerStat.lostShips >> playerStat.points >> playerStat.savedShips;
    return in;
}
