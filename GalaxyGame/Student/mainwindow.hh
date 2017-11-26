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
/**
 * @brief The MainWindow class is responsible for connecting actions between important
 * game objects (Galaxy, GameRunner, DrawableObjectsManager, Handler), is able to catch
 * and handle incoming signals indicating change in game and invoke reactions in UI.
 *
 * Serves as Main view for a game
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent QWidget parent
     * @param handler EventHandler used for handling new game events and changes
     * @param galaxy
     * @param gameRunner
     */
    explicit MainWindow(
            QWidget *parent = 0,
            std::shared_ptr<Common::IEventHandler> handler = 0,
            std::shared_ptr<Student::Galaxy> galaxy = 0,
            std::shared_ptr<Common::IGameRunner> gameRunner = 0);
    /**
     * @brief Destructor
     */
    ~MainWindow();

public Q_SLOTS:
    /**
     * @brief pressedSpace
     * @note handles incoming pressed space signal (user wants to trade or repair ship)
     * @pre PlayerShip player_ has been associated with this object
     * @pre Planet currentPlanet_ which whom can be interacted has been associated with this object
     * @pre StarSystem currentStarSystem where is player located has been associated with this object
     * @pre Question question_ object managing questions in game has been associated with this object
     * @pre Settings setting_ current game settings has been associated with this object
     * @post Exception guarantee: nothrow
     */
    void pressedSpace();

    /**
     * @brief travelToStarSystem
     * @param starSystemId
     * @exception throws UnknownStarSystemException if StarSystem with starSystemId exists
     * @pre PlayerShip player_ has been associated with this object
     * @pre DrawableObjectsManager drawManager_ has been associated with this object
     * @pre Galaxy galaxy_ has been associated with this object
     * @pre gameTimer_ has been associated with this object
     * @post player_ object is realocated from old StarSystem to new one with starSystemId id
     * @post Exception guarantee: basic
     */
    void travelToStarSystem(unsigned starSystemId);

    /**
     * @brief planetsInStarSystemRequest
     * @param id StarSystem id
     * @exception throws Common::ObjectNotFoundException if StarSystem cannot be found
     * @pre DrawableObjectsManager drawManager_ has been associated with this object
     * @pre Galaxy galaxy_ has been associated with this object
     * @pre MapWindow map_ has been associated with this object
     * @post Exception guarantee: strong
     * @post map is updated with new planets
     */
    void planetsInStarSystemRequest(unsigned id);

    /**
     * @brief allQuestionsDone
     * @pre QTime playingTime_ has been associated with this object
     * @post invokes Dialog with info about time needed to complete questions
     * @post Exception guarantee: nothrow
     */
    void allQuestionsDone();

    /**
     * @brief questionCompleted
     * @pre PlayerShip player_ has been associated with this object
     * @pre Settings settings_ has been associated with this object
     * @post player_'s Statistics are updated
     * @post Exception guarantee: nothrow
     */
    void questionCompleted();

    /**
     * @brief shipCallingForHelp
     * @param ship ship which calls for help
     * @exception throws UnknownShipException if ship cannot be found in Ui
     * @pre DrawableObjectsManager drawManager_ has been associated with this object
     * @post ship cannot move, it's location StarSystem is marked as distressed
     * @post Exception guarantee: basic
     */
    void shipCallingForHelp(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief shipSavedFromDistress
     * @param ship ship which was saved
     * @exception throws UnknownShipException if ship cannot be found in Ui
     * @pre DrawableObjectsManager drawManager_ has been associated with this object
     * @pre PlayerShip player_ has been associated with this object
     * @post ship can move, it's location StarSystem is unmarked as distressed if there
     * are no other distresses ships in it
     * @post Exception guarantee: basic
     */
    void shipSavedFromDistress(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief shipAbandoned
     * @param ship ship wich was abandoned
     * @pre DrawableObjectsManager drawManager_ has been associated with this object
     * @pre PlayerShip player_ has been associated with this object
     * @pre MapWindow map_ has been associated with this object
     * @post ship is marked as abandoned, cannot move anymore, StarSystem UI unmarked as distressed if there
     * are no other distresses ships in it
     * @post Exception guarantee: nothrow
     */
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief exceptionInShipExecution
     * @param ship
     * @param msg
     * @post Common::exceptionInShipExecution happens and program is forced to quit
     */
    void exceptionInShipExecution(std::shared_ptr<Common::Ship> ship, std::string const& msg);

private:
    //! MainWindows's ui
    Ui::MainWindow *ui;

    //! EventHandler used for handling new game events and changes
    std::shared_ptr<Common::IEventHandler> handler_;

    //! Galaxy
    std::shared_ptr<Student::Galaxy> galaxy_;

    //! gameRunner used to control game flow
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    //! handler used for handling events coming from user actions
    std::shared_ptr<Student::UserActionHandler> userActionHandler_;

    //! drawManager used to handle objects which are to be drawn on StarSystem view scene
    std::shared_ptr<Student::DrawableObjectsManager> drawManager_;

    //! all items existing in galaxy
    std::shared_ptr<Student::ItemsInGalaxy> itemsInGalaxy_;

    //! ship controlled by user
    std::shared_ptr<Student::PlayerShip> player_;

    //! object responsible for Question checking / completing
    std::shared_ptr<Student::Question> question_;

    //! current game settings
    std::shared_ptr<Student::Settings> settings_;

    //! timer responsible for refreshing UI
    QTimer* refreshTimer_ = nullptr;

    //! timer responsible for checking player collision with other objects
    QTimer* collisionTimer_ = nullptr;

    //! timer responsible for invoking game events
    QTimer* gameTimer_ = nullptr;

    //! playing time counter
    QTime* playingTime_ = nullptr;

    //! map showing all starsystems, is used for travelling
    MapWindow* map_ = nullptr;

    //! statistics window showing current player's Statistics
    StatisticsWindow* statsWindow_ = nullptr;

    //! top list window showing previous player's score
    TopListWindow* topListWindow_ = nullptr;

    //! dialog showing current Questions
    QuestionDlg* questionDlg_ = nullptr;

    //! indicates whether is player able to trade with planet
    bool isPlayerTrading_ = false;

    //! current Planet with whom is player_ trading
    std::shared_ptr<Student::Planet> currentPlanet_;

    //! StarSystem location of player_
    std::shared_ptr<Common::StarSystem> currentStarSystem_;

    //! vector keeping track of all ships in distress
    std::vector<std::shared_ptr<Common::Ship>> shipsInDistress_;

    //! indicates whether is player able to save ship
    bool isNPCShipNear_ = false;

    //! current NPC ship which is player_ saving
    std::shared_ptr<Common::Ship> currentNPCShip_;

    //! user's choice of the name
    QString playerName_;

    /**
     * @brief markQuestionStarSystems Mark star system in travel map with question icon
     * @pre map_ has been associated with this object
     * @pre question_ has been associated with this object
     * @pre galaxy_ has been associated with this object
     */
    void markQuestionStarSystems();

    /**
     * @brief startGame Generate new world and start game
     */
    void startGame();
    void loadSettings();
    void saveSettings();
    void createPlayer();
    bool isNameCorrect(QString name);
    void showDialog(std::string msg, bool quitProgram);
    void showErrorDialog(std::string msg, bool quitProgram);
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
    void changeFocus();

Q_SIGNALS:
    void startCollisionTimer();
    void stopCollisionTimer();
};

#endif // MAINWINDOW_H
