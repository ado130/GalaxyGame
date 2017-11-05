#include "statisticswindow.hh"
#include "ui_statisticswindow.h"

StatisticsWindow::StatisticsWindow(std::shared_ptr<PlayerShip> player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
    ui->shipNameLbl->setText(QString::fromStdString(player->getName()));
    fillStatistics(player->getStatistics());
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::fillStatistics(Student::Statistics stats)
{
    ui->creditsLbl->setText(QString::number(stats.getCreditBalance()));
    ui->pointsLbl->setText(QString::number(stats.getPoints()));
    ui->lostShipsLbl->setText(QString::number(stats.getLostShips()));
    ui->savedShipsLbl->setText(QString::number(stats.getSavedShips()));
    ui->completedQuestsLbl->setText(QString::number(stats.getCompletedQuests()));
    ui->destroyedShipsLbl->setText(QString::number(stats.getDestroyedShips()));
}
