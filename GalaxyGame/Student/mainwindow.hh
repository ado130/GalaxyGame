#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QGraphicsScene>
#include <memory>
#include <QMap>
#include <QPair>
#include <QList>

#include "galaxy.hh"
#include "utility.hh"
#include "igamerunner.hh"
#include "mapwindow.hh"
#include "useractionhandler.hh"
#include "starsystemscene.hh"
#include "drawableobjectsmanager.hh"
#include "itemsingalaxy.hh"

class PlayerShipUi;
class NPCShipUi;
class Planet;
class QThread;

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

public Q_SLOTS:
    void pressedSpace();
//    void shipMovement(std::shared_ptr<Common::Ship> ship, Common::Point from, Common::Point to);
    void travelToStarSystem(unsigned starSystemId);
private:
    Ui::MainWindow *ui;

    std::shared_ptr<Common::IEventHandler> handler_;
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;
    std::shared_ptr<Student::UserActionHandler> userActionHandler_;
    std::shared_ptr<Student::DrawableObjectsManager> drawManager_;
    std::shared_ptr<ItemsInGalaxy> itemsInGalaxy_;
    std::shared_ptr<PlayerShip> player_;


    QTimer *refreshTimer_ = nullptr;
    QTimer *collisionTimer_ = nullptr;
    QTimer *gameTimer_ = nullptr;
//    Student::StarSystemScene *scene_ = nullptr;
    MapWindow *map_ = nullptr;
    QMap<QString, QVariant> playerScore_;
    bool isPlayerTrading_ = false;

    void startGame();
    void loadSettings();
    void saveSettings();
    void createPlayer();

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
