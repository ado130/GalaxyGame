#ifndef ISTATISTICS_HH
#define ISTATISTICS_HH

#ifdef English_dox
/**
 *@file
 * @brief Defines the interface which keeps track of the game state
 */
#endif
namespace Common {

#ifdef English_dox
/**
 * @brief Defines the interface for the concrete statistics
 *
 *
 * @invariant getCreditBalance() > MAX_LOAN_ALLOWANCE && getPoints() > 0
 */
#endif
class IStatistics
{
public:
#ifdef English_dox
    /**
     * @brief Default constructor for the interface (exists for the sake of documentation).
     * @post Initial values are set according to the selection
     */
#endif
    IStatistics() = default;

#ifdef English_dox
    /**
     * @brief Default destructor for the interface (needed since a base class should have a virtual destructor)
     */
#endif
    virtual ~IStatistics() = default;

#ifdef English_dox
    /**
     * @brief addSavedShip increases the number of ships saved from distress
     *
     */
#endif
    virtual void addSavedShip() = 0;

#ifdef English_dox
    /**
      *@brief getSavedShips returns the number of saved ships
      */
#endif
    virtual unsigned getSavedShips() const = 0;

#ifdef English_dox
    /**
     * @brief addLostShip increases the number of ships lost (the ones that have left the galaxy)
     */
#endif
    virtual void addLostShip() = 0;

#ifdef English_dox
    /**
     * @brief getLostShips returns the number of lost ships
     */
#endif
    virtual unsigned getLostShips() const = 0;

#ifdef English_dox
    /**
     * @brief addPoints increses the points of the player by the given amount
     * @param amount Points to be added
     */
#endif
    virtual void addPoints(unsigned amount) = 0;

#ifdef English_dox
    /**
     * @brief reducePoints reduces the points of the player by the given amount
     * @param amount Points to be reduced
     * @exception StateException, if the invariant gets broken
     */
#endif
    virtual void reducePoints(unsigned amount) = 0;

#ifdef English_dox
    /**
     * @brief getPoints returns the total points of the players
     */
#endif
    virtual unsigned getPoints() const = 0;

#ifdef English_dox
    /**
     * @brief addCredits adds credits to the player's account
     * @param amount Credits to be added
     */
#endif
    virtual void addCredits(unsigned amount) = 0;

#ifdef English_dox
    /**
     * @brief reduceCredits reduces credits from the player's account
     * @param amount Credits to be removed
     * @exception StateException, if the invariant gets broken
     */
#endif
    virtual void reduceCredits(unsigned amount) = 0;


#ifdef English_dox
    /**
     * @brief getCreditBalance returns the number of credits left
     */
#endif
    virtual int getCreditBalance() const = 0;


};

}//Common

#endif // ISTATISTICS_HH
