#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"
#include "stateexception.hh"

namespace Student {

class Statistics : public Common::IStatistics
{
public:
    Statistics(int MAX_LOAN_ALLOWANCE = 5000);

     void addSavedShip();
     unsigned getSavedShips() const;

     void addLostShip();
     unsigned getLostShips() const;

     void addPoints(unsigned amount);
     void reducePoints(unsigned amount);
     unsigned getPoints() const;

     void addCredits(unsigned amount);
     void reduceCredits(unsigned amount);
     int getCreditBalance() const;

     void setMaxLoanAllowance(int maxLoan);
     int getMaxLoanAllowance();

private:

     unsigned savedShips = 0;
     unsigned lostShips = 0;
     unsigned points = 0;
     int credits = 0;

     // ToDo: what is this for? Where is it set? (create "settings" class)
     int MAX_LOAN_ALLOWANCE;


};
}//Student

#endif // STATISTICS_HH
