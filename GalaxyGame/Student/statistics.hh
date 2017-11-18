#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"

#include <memory>
#include "eventhandler.hh"
#include <QDataStream>
#include <QMap>

namespace Student {

class Statistics : public Common::IStatistics
{
public:

    struct playerStat
    {
        unsigned savedShips;
        unsigned lostShips;
        unsigned points;
        int credits;
        unsigned destroyedShips;
        unsigned completedQuest;
    };

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

     Student::Statistics::playerStat getPlayerStat();
private:
     unsigned savedShips_ = 0;
     unsigned lostShips_ = 0;
     unsigned points_ = 0;
     int credits_ = 0;
     unsigned destroyedShips_ = 0;
     unsigned completedQuest_ = 0;

     int MAX_LOAN_ALLOWANCE;
     std::shared_ptr<Student::EventHandler> handler_;

};
}//Student


#endif // STATISTICS_HH
