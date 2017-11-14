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
private:
    void applyDefaultSettings();
    double creditProfitFromSale_;
    int maxCreditAllowance_;
    int initialPlayerCredit_;
    int pointsFromQuestion_;
};
}

#endif // SETTINGS_HH
