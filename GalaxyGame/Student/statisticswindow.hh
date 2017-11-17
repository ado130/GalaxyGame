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

    bool isNeedForUpdate() { return needForUpdate_; }
    void fillStatistics(Student::Statistics *stats);

public Q_SLOTS:
    void setNeedForUpdate(bool update) { needForUpdate_ = update; }

private:
    Ui::StatisticsWindow *ui;
    bool needForUpdate_;
};

#endif // STATISTICSWINDOW_H
