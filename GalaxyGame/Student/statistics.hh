#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"
namespace Student {

class Statistics : public Common::IStatistics
{
public:
    Statistics();

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

private:

};
}//Student

#endif // STATISTICS_HH
