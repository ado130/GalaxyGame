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
   fillTopTen(playerStat);
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
    ui->destroyedShipsLbl->setText(QString::number(stats->getDestroyedShips()));
}

void StatisticsWindow::fillTopTen(Student::Statistics* stats)
{
    QMap<QString, Student::Statistics::playerStat> items = stats->getTotalStat();

    if(items.isEmpty()) return;

    QList<QPair<QString, Student::Statistics::playerStat> > sorted = sortTopTen(items);

    QStringList headerLabels;
    headerLabels.push_back(tr("Name"));
    headerLabels.push_back(tr("Points"));
    ui->treeWidget->setColumnCount(headerLabels.count());
    ui->treeWidget->setHeaderLabels(headerLabels);

    for(auto k : sorted)
    {
        addRoot(k.first, "Points", k.second);
    }
}

void StatisticsWindow::addRoot(QString name, QString description, Student::Statistics::playerStat stat)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, name);
    item->setText(1, description);

    addChild(item, "Points", QString::number(stat.points));
    addChild(item, "Credits", QString::number(stat.credits));
    addChild(item, "Saved ships", QString::number(stat.savedShips));
    addChild(item, "Destroyed ships", QString::number(stat.destroyedShips));
    addChild(item, "Completed quests", QString::number(stat.completedQuest));
    addChild(item, "Lost ships", QString::number(stat.lostShips));
}

void StatisticsWindow::addChild(QTreeWidgetItem* parent ,QString name, QString description)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, description);
    parent->addChild(item);
}

QList<QPair<QString, Student::Statistics::playerStat> > StatisticsWindow::sortTopTen(QMap<QString, Student::Statistics::playerStat> stats)
{
    QList<QPair<QString, Student::Statistics::playerStat> > sortedStats;
    QPair<QString, Student::Statistics::playerStat> pair;
    pair.first = stats.firstKey();
    pair.second = stats.first();
    sortedStats.insert(0, pair);

    auto it = stats.constBegin() + 1;       // skip the first
    while(it != stats.constEnd())
    {
        int first = it.value().completedQuest + it.value().credits + it.value().destroyedShips - it.value().lostShips + it.value().points + it.value().savedShips;
        int second = sortedStats.last().second.completedQuest + sortedStats.last().second.credits + sortedStats.last().second.destroyedShips - sortedStats.last().second.lostShips + sortedStats.last().second.points + sortedStats.last().second.savedShips;
        pair.first = it.key();
        pair.second = it.value();

        if(first > second)
        {
            sortedStats.push_back(pair);
        }
        else
        {
            sortedStats.push_front(pair);
        }

        ++it;
    }

    return sortedStats;
}
