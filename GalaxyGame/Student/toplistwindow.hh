#ifndef TOPLISTWINDOW_H
#define TOPLISTWINDOW_H

#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "statistics.hh"

#define FILENAME "stats.dat"

namespace Ui {
class TopListWindow;
}

class TopListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TopListWindow(QWidget *parent = 0);
    ~TopListWindow();

    /**
     * @brief saveSettings Method to save settings into variable and file
     * @param name Player name
     * @param stat Stats of the current player name
     */
    void saveSettings(QString name, Student::Statistics::playerStat stat);

    /**
     * @brief loadSettings Method to load top list from the file
     * @pre File exists
     * @post Top list loaded from the file
     */
    void loadSettings();

    /**
     * @brief resetStats Method to reset top list
     */
    void resetStats();
private:
    Ui::TopListWindow *ui;
    void fillTopTen();

    /**
     * @brief addRoot Add new root into tree widget
     * @param name Name of the root
     * @param description Description of the root
     * @param stat Player statistics
     */
    void addRoot(QString name, QString description, Student::Statistics::playerStat stat);

    /**
     * @brief addChild Add new child into root
     * @param parent Parent of new child
     * @param name Name of the child
     * @param description Description of the child
     * @pre Check if parent exists
     */
    void addChild(QTreeWidgetItem *parent, QString name, QString description);

    /**
     * @brief sortTopTen Method to sort statistics by reached points
     * @param stats Map of statistics to sort; key is player name and value is player statistics
     * @return Return a list of pair, player name -- player statistics
     */
    QList<QPair<QString, Student::Statistics::playerStat> > sortTopTen(QMap<QString, Student::Statistics::playerStat> stats);

    //! totalStat_ is used to store players statistics
    QMap<QString, Student::Statistics::playerStat> totalStat_;
};

QDataStream &operator<<(QDataStream &out, const Student::Statistics::playerStat &playerStat);
QDataStream &operator>>(QDataStream &in, const Student::Statistics::playerStat &playerStat);


#endif // TOPLISTWINDOW_H
