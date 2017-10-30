#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include <QMap>
#include <QPair>
#include <QList>

#include "galaxy.hh"
#include "utility.hh"
#include "igamerunner.hh"

class PlayerShip;
class NPCShip;
class StarPlanet;
class QThread;

namespace Ui {
class MainWindow;
}

typedef QList< QPair<std::shared_ptr<Common::Ship>, NPCShip*> > shipUI_t;
typedef QList< QPair<std::shared_ptr<Common::StarSystem>, StarPlanet*> > starSystemUI_t;

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

public Q_SLOTS:
    void pressedSpace();
    void shipMovement(std::shared_ptr<Common::Ship> ship, int diffX, int diffY);
    void shipEvent(std::shared_ptr<Common::Ship> ship, bool newShip);
private:
    Ui::MainWindow *ui;

    std::shared_ptr<Common::IEventHandler> handler_;
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    QTimer *refreshTimer_ = nullptr;
    QTimer *collisionTimer_ = nullptr;
    QTimer *gameTimer_ = nullptr;
    QGraphicsScene *scene_ = nullptr;
    PlayerShip *player_ = nullptr;
    QMap<QString, QVariant> playerScore_;
    shipUI_t shipList_;
    starSystemUI_t starSystemList_;

    void startGame();
    void loadSettings();
    void saveSettings();
    void createPlayer();
    void createStarSystem();
    void checkCollision();
    QGraphicsItem *getSceneShip(std::shared_ptr<Common::Ship> ship);
private Q_SLOTS:
    void on_actionNew_Game_triggered();
    void on_actionExit_triggered();
    void on_pbNewGame_clicked();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void refreshUI();
    void executeCollisionCheck();
    void on_actionMy_statistics_triggered();
    void gameEvent();
};

#endif // MAINWINDOW_H
