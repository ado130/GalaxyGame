#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"

#include <memory>
#include "eventhandler.hh"

namespace Student {

class Statistics : public Common::IStatistics
{
public:
    Statistics(int MAX_LOAN_ALLOWANCE = 100, std::shared_ptr<Student::EventHandler> handler = nullptr);
    ~Statistics();

     void addSavedShip();
     unsigned getSavedShips() const;

     void addLostShip();
     unsigned getLostShips() const;

     void addDestroyedShip();
     unsigned getDestroyedShips() const;

     void addCompletedQuest();
     unsigned getCompletedQuests() const;

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
     unsigned destroyedShips = 0;
     unsigned completedQuest = 0;

     int MAX_LOAN_ALLOWANCE;
     std::shared_ptr<Student::EventHandler> handler_;

};
}//Student

#endif // STATISTICS_HH
