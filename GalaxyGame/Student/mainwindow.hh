#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QMap>
#include <QPair>
#include <QList>
#include <QVector>

#include "galaxy.hh"
#include "utility.hh"
#include "igamerunner.hh"
#include "mapwindow.hh"
#include "statisticswindow.hh"
#include "useractionhandler.hh"
#include "starsystemscene.hh"
#include "drawableobjectsmanager.hh"
#include "itemsingalaxy.hh"
#include "question.hh"
#include "questiondlg.hh"
#include "settings.hh"
#include "toplistwindow.hh"

class PlayerShipUi;
class NPCShipUi;
class Planet;

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
    void planetsInStarSystemRequest(unsigned id);
    void allQuestionsDone();
    void questionCompleted();
    void shipCallingForHelp(std::shared_ptr<Common::Ship> ship);
    void shipSavedFromDistress(std::shared_ptr<Common::Ship> ship);
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Common::IEventHandler> handler_;
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<Common::IGameRunner> gameRunner_;
    std::shared_ptr<Student::UserActionHandler> userActionHandler_;
    std::shared_ptr<Student::DrawableObjectsManager> drawManager_;
    std::shared_ptr<ItemsInGalaxy> itemsInGalaxy_;
    std::shared_ptr<PlayerShip> player_;
    std::shared_ptr<Student::Question> question_;
    std::shared_ptr<Student::Settings> settings_;


    QTimer* refreshTimer_ = nullptr;
    QTimer* collisionTimer_ = nullptr;
    QTimer* gameTimer_ = nullptr;
    QTime* playingTime_ = nullptr;
    MapWindow* map_ = nullptr;
    StatisticsWindow* statsWindow_ = nullptr;
    TopListWindow* topListWindow_ = nullptr;
    QuestionDlg* questionDlg_ = nullptr;
    QMap<QString, QVariant> playerScore_;
    bool isPlayerTrading_ = false;
    std::shared_ptr<Student::Planet> currentPlanet_;
    std::shared_ptr<Common::StarSystem> currentStarSystem_;
    std::vector<std::shared_ptr<Common::Ship>> shipsInDistress_;
    QPixmap pixDistressed_;
    QPixmap pixAbandoned_;
    bool isNPCShipNear_ = false;
    std::shared_ptr<Common::Ship> currentNPCShip_;
    QString playerName_;

    void startGame();
    void loadSettings();
    void saveSettings();
    void createPlayer();
    bool isNameCorrect(QString name);
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

    void on_pbQuestions_clicked();

    void on_pbEndGame_clicked();

    void on_actionTop_list_triggered();

    void on_actionDefault_Settings_triggered();

    void on_actionReset_top_list_triggered();

Q_SIGNALS:
    void startCollisionTimer();
    void stopCollisionTimer();
};

#endif // MAINWINDOW_H
