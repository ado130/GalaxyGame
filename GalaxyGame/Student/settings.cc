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

int Student::Settings::getPointsFromSaving()
{
    return pointsFromSaving_;
}

int Student::Settings::getCreditsFromSaving()
{
    return creditsFromSaving_;
}

void Student::Settings::applyDefaultSettings()
{
    creditProfitFromSale_ = 0.5;
    maxCreditAllowance_ = 100;
    initialPlayerCredit_ = 10;
    pointsFromQuestion_ = 1;
    pointsFromSaving_ = 2;
    creditsFromSaving_ = 3;
}
