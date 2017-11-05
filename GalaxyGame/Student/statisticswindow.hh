#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include "playership.hh"
#include "statistics.hh"

#include <QDialog>

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    StatisticsWindow(std::shared_ptr<PlayerShip> player, QWidget *parent = 0);
    ~StatisticsWindow();

private:
    Ui::StatisticsWindow *ui;
    void fillStatistics(Student::Statistics stats);
};

#endif // STATISTICSWINDOW_H
