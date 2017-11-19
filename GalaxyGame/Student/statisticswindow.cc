#include "statisticswindow.hh"
#include "ui_statisticswindow.h"

#include <QPair>

StatisticsWindow::StatisticsWindow(Student::Statistics* playerStat, QString playerName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
   ui->shipNameLbl->setText(playerName + " battle ship");
   fillStatistics(playerStat);
   needForUpdate_ = false;

}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::fillStatistics(Student::Statistics* stats)
{
    ui->creditsLbl->setText(QString::number(stats->getCreditBalance()));
    ui->pointsLbl->setText(QString::number(stats->getPoints()));
    ui->lostShipsLbl->setText(QString::number(stats->getLostShips()));
    ui->savedShipsLbl->setText(QString::number(stats->getSavedShips()));
    ui->completedQuestsLbl->setText(QString::number(stats->getCompletedQuests()));
}
