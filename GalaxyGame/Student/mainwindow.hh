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
#include "mapwindow.hh"
#include "useractionhandler.hh"

class PlayerShip;
class NPCShip;
class StarPlanet;
class QThread;

namespace Ui {
class MainWindow;
}

typedef QList< QPair<std::shared_ptr<Common::Ship>, NPCShip*> > shipUI_t;
typedef QMultiMap<unsigned int, QPair<std::shared_ptr<Common::StarSystem>, StarPlanet*> > starPlanetUI_t;

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
    void travelToStarSystem(unsigned starSystemId);
private:
    Ui::MainWindow *ui;

    std::shared_ptr<Common::IEventHandler> handler_;
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;
    std::shared_ptr<Student::UserActionHandler> userActionHandler_;

    QTimer *refreshTimer_ = nullptr;
    QTimer *collisionTimer_ = nullptr;
    QTimer *gameTimer_ = nullptr;
    QGraphicsScene *scene_ = nullptr;
    PlayerShip *player_ = nullptr;
    MapWindow *map_ = nullptr;
    QMap<QString, QVariant> playerScore_;
    shipUI_t shipList_;
    starPlanetUI_t starPlanetList_;
    bool isPlayerTrading_ = false;

    void startGame();
    void loadSettings();
    void saveSettings();
    void createPlayer();
    void createPlanetsForStarSystem();
    QGraphicsItem *getSceneShip(std::shared_ptr<Common::Ship> ship);
    QGraphicsItem *getSceneStarSystem(std::shared_ptr<Common::StarSystem> starSystem);
    StarPlanet *getStarPlanetByItem(QGraphicsItem *item);
private Q_SLOTS:
    void on_actionNew_Game_triggered();
    void on_actionExit_triggered();
    void on_pbNewGame_clicked();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void refreshUI();
    void on_actionMy_statistics_triggered();
    void gameEvent();
    void checkCollision();
    void on_pbShowMap_clicked();


Q_SIGNALS:
    void startCollisionTimer();
    void stopCollisionTimer();
};

#endif // MAINWINDOW_H
