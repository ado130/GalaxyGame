#ifndef TOPLISTWINDOW_H
#define TOPLISTWINDOW_H

#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "statistics.hh"

namespace Ui {
class TopListWindow;
}

class TopListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TopListWindow(QWidget *parent = 0);
    ~TopListWindow();

    void saveSettings(QString name, Student::Statistics::playerStat stat);
    void loadSettings();

    void resetStats();
private:
    Ui::TopListWindow *ui;
    void fillTopTen();
    void addRoot(QString name, QString description, Student::Statistics::playerStat stat);
    void addChild(QTreeWidgetItem *parent, QString name, QString description);
    QList<QPair<QString, Student::Statistics::playerStat> > sortTopTen(QMap<QString, Student::Statistics::playerStat> stats);

    QMap<QString, Student::Statistics::playerStat> totalStat_;
};

QDataStream &operator<<(QDataStream &out, const Student::Statistics::playerStat &playerStat);
QDataStream &operator>>(QDataStream &in, const Student::Statistics::playerStat &playerStat);


#endif // TOPLISTWINDOW_H
