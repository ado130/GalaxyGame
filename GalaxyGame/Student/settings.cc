#include "settings.hh"

#include <QSettings>
#include <QFile>

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
    QSettings settings("settings.ini", QSettings::IniFormat);

    if(!QFile("settings.ini").exists())
    {
        creditProfitFromSale_ = 0.5;
        maxCreditAllowance_ = 100;
        initialPlayerCredit_ = 10;
        pointsFromQuestion_ = 1;
        pointsFromSaving_ = 2;
        creditsFromSaving_ = 3;

        settings.setValue("CreditProfitFromSale", creditProfitFromSale_);
        settings.setValue("MaxCreditAllowance", maxCreditAllowance_);
        settings.setValue("InitialPlayerCredit", initialPlayerCredit_);
        settings.setValue("PointsFromQuestion", pointsFromQuestion_);
        settings.setValue("PointsFromSaving", pointsFromSaving_);
        settings.setValue("CreditsFromSaving", creditsFromSaving_);
    }

    creditProfitFromSale_ = settings.value("CreditProfitFromSale", 0.5).toInt();
    maxCreditAllowance_ = settings.value("MaxCreditAllowance", 100).toInt();
    initialPlayerCredit_ = settings.value("InitialPlayerCredit", 10).toInt();
    pointsFromQuestion_ = settings.value("PointsFromQuestion", 1).toInt();
    pointsFromSaving_ = settings.value("PointsFromSaving", 2).toInt();
    creditsFromSaving_ = settings.value("CreditsFromSaving", 3).toInt();
}

void Student::Settings::setDefault()
{
    creditProfitFromSale_ = 0.5;
    maxCreditAllowance_ = 100;
    initialPlayerCredit_ = 10;
    pointsFromQuestion_ = 1;
    pointsFromSaving_ = 2;
    creditsFromSaving_ = 3;

    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.setValue("CreditProfitFromSale", creditProfitFromSale_);
    settings.setValue("MaxCreditAllowance", maxCreditAllowance_);
    settings.setValue("InitialPlayerCredit", initialPlayerCredit_);
    settings.setValue("PointsFromQuestion", pointsFromQuestion_);
    settings.setValue("PointsFromSaving", pointsFromSaving_);
    settings.setValue("CreditsFromSaving", creditsFromSaving_);
}
