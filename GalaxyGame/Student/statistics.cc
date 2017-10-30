#include "statistics.hh"

Student::Statistics::Statistics(int maxLoanAllowance):
    MAX_LOAN_ALLOWANCE(maxLoanAllowance)
{

}

void Student::Statistics::addSavedShip()
{
    savedShips++;
}

unsigned Student::Statistics::getSavedShips() const
{
    return savedShips;
}

void Student::Statistics::addLostShip()
{
    lostShips++;
}

unsigned Student::Statistics::getLostShips() const
{
    return lostShips;
}

// ToDo: unit test
void Student::Statistics::addDestroyedShip()
{
    destroyedShips++;
}

// ToDo: unit test
unsigned Student::Statistics::getDestroyedShips() const
{
    return this->destroyedShips;
}

// ToDo: unit test
void Student::Statistics::addCompletedQuest()
{
    completedQuest++;
}

// ToDo: unit test
unsigned Student::Statistics::getCompletedQuests() const
{
    return completedQuest;
}

void Student::Statistics::addPoints(unsigned amount)
{
    points += amount;
}

void Student::Statistics::reducePoints(unsigned amount)
{
    if(amount > points){
//        Todo: error: undefined reference
//        throw Common::StateException("Amount of points too low! Cannot reduce.");
    }
    else{
        points -= amount;
    }
}

unsigned Student::Statistics::getPoints() const
{
    return points;
}

void Student::Statistics::addCredits(unsigned amount)
{
    credits += amount;
}

void Student::Statistics::reduceCredits(unsigned amount)
{
    if(amount > credits+MAX_LOAN_ALLOWANCE){
//        Todo: error: undefined reference
//        throw Common::StateException("Amount of credits too low! Cannot reduce.");
    }
    else{
        credits -= amount;
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
