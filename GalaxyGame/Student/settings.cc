#include "settings.hh"

Student::Settings::Settings()
{
    applyDefaultSettings();
}

double Student::Settings::getCreditProfitFromSale()
{
    return creditProfitFromSale_;
}

int Student::Settings::getMaxCreditAllowance()
{
    return maxCreditAllowance_;
}

int Student::Settings::getInitialPlayerCredit()
{
    return initialPlayerCredit_;
}

int Student::Settings::getPointsFromQuestion()
{
    return pointsFromQuestion_;
}

void Student::Settings::applyDefaultSettings()
{
    creditProfitFromSale_ = 0.5;
    maxCreditAllowance_ = 100;
    initialPlayerCredit_ = 10;
    pointsFromQuestion_ = 1;
}
