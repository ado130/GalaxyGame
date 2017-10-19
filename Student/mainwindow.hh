#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include "galaxy.hh"
#include "utility.hh"
#include "igamerunner.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, std::shared_ptr<Student::Galaxy> galaxy_ = 0, std::shared_ptr<Common::IGameRunner> gameRunner_ = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    QGraphicsScene *scene_;
};

#endif // MAINWINDOW_H
