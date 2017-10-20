#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include "galaxy.hh"
#include "utility.hh"
#include "igamerunner.hh"

class PlayerShip;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(
            QWidget *parent = 0,
            std::shared_ptr<Common::IEventHandler> handler = 0,
            std::shared_ptr<Student::Galaxy> galaxy = 0,
            std::shared_ptr<Common::IGameRunner> gameRunner = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Common::IEventHandler> handler_;
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    QTimer *timer;
    std::shared_ptr<QGraphicsScene> scene_;
    PlayerShip *player;

    void startGame();

private slots:
    void on_actionNew_Game_triggered();
    void on_actionExit_triggered();
    void on_pbNewGame_clicked();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void refreshUI();
};

#endif // MAINWINDOW_H
