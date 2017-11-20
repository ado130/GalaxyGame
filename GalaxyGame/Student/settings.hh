#ifndef SETTINGS_HH
#define SETTINGS_HH

namespace Student {
/**
 * @brief Settings class stores different kind of values
 * used in a game
 */
class Settings
{
public:
    /**
     * @brief Constructor.
     */
    Settings();

    /**
     * @brief getCreditProfitFromSale
     * @return globaly set profit as a double value
     * @post Exception garantee: nothrow
     */
    double getCreditProfitFromSale();

    /**
     * @brief getMaxCreditAllowance
     * @return max credit allowance limit
     * @post Exception garantee: nothrow
     */
    int getMaxCreditAllowance();

    /**
     * @brief getInitialPlayerCredit
     * @return initial credit set for playerShip when game starts
     * @post Exception garantee: nothrow
     */
    int getInitialPlayerCredit();

    /**
     * @brief getPointsFromQuestion
     * @return amount of points gained from question completed
     * @post Exception garantee: nothrow
     */
    int getPointsFromQuestion();

    /**
     * @brief getPointsFromSaving
     * @return amount of points gained from ship saved
     * @post Exception garantee: nothrow
     */
    int getPointsFromSaving();

    /**
     * @brief getCreditsFromSaving
     * @return amount of credits gained from ship saved
     * @post Exception garantee: nothrow
     */
    int getCreditsFromSaving();

    /**
     * @brief setDefault initiates default values and stores them in file
     * @post Exception garantee: nothrow
     * @post Default Settings values are stored in a file
     */
    void setDefault();
private:
    /**
     * @brief applyDefaultSettings applies default values to Settings object
     * @post Exception garantee: nothrow
     * @post Settings attibutes has their default values
     */
    void applyDefaultSettings();

    //! globaly set profit as a double value
    double creditProfitFromSale_;

    //! maximum credit allowance limit
    int maxCreditAllowance_;

    //! initial credit set for playerShip when game starts
    int initialPlayerCredit_;

    //! amount of points gained from question completed
    int pointsFromQuestion_;

    //! amount of points gained from ship saved
    int pointsFromSaving_;

    //! amount of credits gained from ship saved
    int creditsFromSaving_;
};
}

#endif // SETTINGS_HH
