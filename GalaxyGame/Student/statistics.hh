#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"

#include <memory>
#include "eventhandler.hh"
#include <QDataStream>
#include <QMap>

namespace Student {
/**
 * @brief Defines the interface for statistics class.
 *
 * @invariant getPoints() >= 0
 * @invariant getCreditBalance() >= MAX_LOAN_ALLOWANCE
 * MAX_LOAN_ALLOWANCE is the limit that the player is allowed to have debt.
 * The actual value is to be decided by the implementer of inherited class.
 */
class Statistics : public Common::IStatistics
{
public:
    //! struct used for files
    struct playerStat
    {
        unsigned savedShips;
        unsigned lostShips;
        unsigned points;
        int credits;
        unsigned completedQuest;
    };

    /**
     * @brief Constructor.
     * @param MAX_LOAN_ALLOWANCE limit that the player is allowed to have debt
     * @param handler EventHandler
     */
    Statistics(int MAX_LOAN_ALLOWANCE = 10, std::shared_ptr<Student::EventHandler> handler = nullptr);

    /**
     * @brief Destructor.
     */
    ~Statistics();

    /**
     * @brief addSavedShip.
     * @post savedShips_ attribute is increased by one
     * @post handler is informed about change
     * @post Exception guarantee: nothrow
     */
     void addSavedShip();

     /**
      * @brief getSavedShips.
      * @return number of saved ships
      * @post Exception guarantee: nothrow
      */
     unsigned getSavedShips() const;

     /**
      * @brief addLostShip.
      * @post lostShips_ attribute is increased by one
      * @post handler is informed about change
      * @post Exception guarantee: nothrow
      */
     void addLostShip();

     /**
      * @brief getLostShips.
      * @return number of lost ships
      * @post Exception guarantee: nothrow
      */
     unsigned getLostShips() const;

     /**
      * @brief addCompletedQuest.
      * @post completedQuest_ attribute is increased by one
      * @post handler is informed about change
      * @post Exception guarantee: nothrow
      */
     void addCompletedQuest();

     /**
      * @brief getCompletedQuests.
      * @return number of completed quests
      * @post Exception guarantee: nothrow
      */
     unsigned getCompletedQuests() const;

     /**
      * @brief addPoints.
      * @param amount amout of points to be added
      * @post points_ attribute is increased by amount
      * @post handler is informed about change
      * @post Exception guarantee: nothrow
      */
     void addPoints(unsigned amount);
     /**
      * @brief reducePoints.
      * @param amount amout of points to be reduced
      * @post points_ attribute is decreased by amount
      * @post handler is informed about change
      * @post Exception guarantee: nothrow
      */
     void reducePoints(unsigned amount);

     /**
      * @brief getPoints.
      * @return number of points
      * @post Exception guarantee: nothrow
      */
     unsigned getPoints() const;

     /**
      * @brief addCredits.
      * @param amount amout of credits to be added
      * @post credits_ attribute is increased by amount
      * @post handler is informed about change
      * @post Exception guarantee: nothrow
      */
     void addCredits(unsigned amount);

     /**
      * @brief reduceCredits.
      * @param amount amout of credits to be reduced
      * @post credits_ attribute is decreased by amount
      * @post handler is informed about change
      * @post Exception guarantee: nothrow
      */
     void reduceCredits(unsigned amount);

     /**
      * @brief getCreditBalance.
      * @return number of credits
      * @post Exception guarantee: nothrow
      */
     int getCreditBalance() const;

     /**
      * @brief setMaxLoanAllowance.
      * @param maxLoan new loan limit
      * @post MAX_LOAN_ALLOWANCE is changed
      * @post Exception guarantee: nothrow
      */
     void setMaxLoanAllowance(int maxLoan);

     /**
      * @brief getMaxLoanAllowance.
      * @return maximum loan limit
      * @post Exception guarantee: nothrow
      */
     int getMaxLoanAllowance();

     /**
      * @brief getPlayerStat.
      * @return player Statistics as struct
      * @post Exception guarantee: nothrow
      */
     Student::Statistics::playerStat getPlayerStat();
private:
     //! number of all ships saved
     unsigned savedShips_ = 0;

     //! number of all ships lost
     unsigned lostShips_ = 0;

     //! number of all points gained
     unsigned points_ = 0;

     //! number of credits
     int credits_ = 0;

     //! number of all quests completed
     unsigned completedQuest_ = 0;

     //! limit that the player is allowed to have debt
     int MAX_LOAN_ALLOWANCE;

     //! handler spreading news about changes
     std::shared_ptr<Student::EventHandler> handler_;
};
}//Student


#endif // STATISTICS_HH
