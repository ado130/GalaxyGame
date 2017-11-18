#ifndef SETTINGS_HH
#define SETTINGS_HH

namespace Student {
class Settings
{
public:
    //default constructor with default settings
    Settings();

    double getCreditProfitFromSale();
    int getMaxCreditAllowance();
    int getInitialPlayerCredit();
    int getPointsFromQuestion();
    int getPointsFromSaving();
    int getCreditsFromSaving();

    void setDefault();
private:
    void applyDefaultSettings();

    double creditProfitFromSale_;
    int maxCreditAllowance_;
    int initialPlayerCredit_;
    int pointsFromQuestion_;
    int pointsFromSaving_;
    int creditsFromSaving_;
};
}

#endif // SETTINGS_HH
