#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include "playership.hh"
#include "statistics.hh"

#include <QDialog>
#include <QPair>
#include <QList>
#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace Ui {
class StatisticsWindow;
}
/**
 * @brief The StatisticsWindow class showing data from Statistics
 */
class StatisticsWindow : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief StatisticsWindow constructor
     * @param playerStat Statistics object from current player
     * @param playerName name from current player
     * @param parent QWidget parent
     */
    StatisticsWindow(Student::Statistics *playerStat, QString playerName, QWidget *parent = 0);

    /**
     * @brief Destructor
     */
    ~StatisticsWindow();

    /**
     * @brief isNeedForUpdate
     * @return true if Statistics object changed and UI needs to be updated
     * @post Exception guarantee: nothrow
     */
    bool isNeedForUpdate() { return needForUpdate_; }

    /**
     * @brief fillStatistics
     * @param stats current Statistics to be displayed
     * @post labels in window are updated according to given stats
     * @post Exception guarantee: nothrow
     */
    void fillStatistics(Student::Statistics *stats);

public Q_SLOTS:
    /**
     * @brief setNeedForUpdate
     * @param update
     * @post needForUpdate_ is changes according to update param
     * @post Exception guarantee: nothrow
     */
    void setNeedForUpdate(bool update) { needForUpdate_ = update; }

private:
    //! ui of StatisticsWindow
    Ui::StatisticsWindow *ui;

    //! needForUpdate_ tells whether there was a change to Statistics and UI labels has to be updated
    bool needForUpdate_;
};

#endif // STATISTICSWINDOW_H
