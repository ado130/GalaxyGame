#include "toplistwindow.hh"
#include "ui_toplistwindow.h"

#include <QDataStream>
#include <QFile>

TopListWindow::TopListWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopListWindow)
{
    ui->setupUi(this);

    loadSettings();
    fillTopTen();
}

TopListWindow::~TopListWindow()
{
    delete ui;
}

void TopListWindow::fillTopTen()
{
    if(totalStat_.isEmpty()) return;

    QList<QPair<QString, Student::Statistics::playerStat> > sorted = sortTopTen(totalStat_);

    ui->treeWidget->clear();

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

void TopListWindow::addRoot(QString name, QString description, Student::Statistics::playerStat stat)
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

void TopListWindow::addChild(QTreeWidgetItem* parent ,QString name, QString description)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, description);
    parent->addChild(item);
}

QList<QPair<QString, Student::Statistics::playerStat> > TopListWindow::sortTopTen(QMap<QString, Student::Statistics::playerStat> stats)
{
    QList<QPair<QString, Student::Statistics::playerStat> > sortedStats;
    QPair<QString, Student::Statistics::playerStat> pair;
    pair.first = stats.firstKey();
    pair.second = stats.first();
    sortedStats.insert(0, pair);

    auto it = stats.constBegin() + 1;       // skip the first
    while(it != stats.constEnd())
    {
        int first = it.value().completedQuest*3 + it.value().credits + it.value().destroyedShips - it.value().lostShips + it.value().points*2 + it.value().savedShips*2;

        pair.first = it.key();
        pair.second = it.value();

        bool bAdded = false;
        for(int i = 0; i<sortedStats.count(); ++i)
        {
            int second = sortedStats.at(i).second.completedQuest*3 + sortedStats.at(i).second.credits + sortedStats.at(i).second.destroyedShips - sortedStats.at(i).second.lostShips + sortedStats.at(i).second.points*2 + sortedStats.at(i).second.savedShips*2;

            if(first > second)
            {
                sortedStats.insert(i, pair);
                bAdded = true;
                break;
            }
        }

        if(!bAdded)
        {
            sortedStats.push_back(pair);
        }

        ++it;
    }

    return sortedStats;
}

void TopListWindow::loadSettings()
{
    QFile file("stats.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> totalStat_;
}

void TopListWindow::resetStats()
{
    totalStat_.clear();
    ui->treeWidget->clear();
}

void TopListWindow::saveSettings(QString name, Student::Statistics::playerStat stat)
{
    totalStat_[name] = stat;

    QFile file("stats.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << totalStat_;

    fillTopTen();
}

QDataStream &operator<<(QDataStream &out, const Student::Statistics::playerStat &playerStat)
{
    out << playerStat.completedQuest << playerStat.credits << playerStat.destroyedShips << playerStat.lostShips << playerStat.points << playerStat.savedShips;
    return out;
}

QDataStream &operator>>(QDataStream &in, Student::Statistics::playerStat &playerStat)
{
    in >> playerStat.completedQuest >> playerStat.credits >> playerStat.destroyedShips >> playerStat.lostShips >> playerStat.points >> playerStat.savedShips;
    return in;
}
