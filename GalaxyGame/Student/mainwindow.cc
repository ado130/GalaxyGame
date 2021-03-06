#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "initialize.hh"
#include "planet.hh"
#include "playershipui.hh"
#include "wormholedrive.hh"
#include "objectnotfoundexception.hh"
#include "statisticswindow.hh"
#include "playership.hh"
#include "repairaction.hh"
#include "eventhandler.hh"
#include "tradeaction.hh"
#include "unknownshipexception.hh"
#include "unknownstarsystemexception.hh"

#include <QDebug>
#include <QTextEdit>
#include <QTimer>
#include <QBrush>
#include <QInputDialog>
#include <QSettings>
#include <QtConcurrent>
#include <QFuture>
#include <QMessageBox>
#include <cassert>


MainWindow::MainWindow(QWidget *parent,
                       std::shared_ptr<Common::IEventHandler> handler,
                       std::shared_ptr<Student::Galaxy> galaxy,
                       std::shared_ptr<Common::IGameRunner> gameRunner) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    handler_ = handler;
    galaxy_ = galaxy;
    gameRunner_ = gameRunner;
    userActionHandler_ = std::make_shared<Student::UserActionHandler>();
    Ui::StarSystemScene *scene = new Ui::StarSystemScene(this);
    drawManager_ = std::make_shared<Student::DrawableObjectsManager>(scene , userActionHandler_, this);
    itemsInGalaxy_ = std::make_shared<Student::ItemsInGalaxy>();
    question_ = std::make_shared<Student::Question>(galaxy, itemsInGalaxy_);
    settings_ = std::make_shared<Student::Settings>();
    topListWindow_ = new TopListWindow();

    QObject* eventHandlerObj = dynamic_cast<QObject*>(handler.get());
    QObject* userEventHandlerObj = dynamic_cast<QObject*>(userActionHandler_.get());
    QObject* drawManagerObj = dynamic_cast<QObject*>(drawManager_.get());
    QObject* questionObj = dynamic_cast<QObject*>(question_.get());
    connect(eventHandlerObj, SIGNAL(registerShipToUi(std::shared_ptr<Common::Ship>)),
            drawManagerObj, SLOT(registerShip(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(unregisterShipFromUi(std::shared_ptr<Common::Ship>)),
            drawManagerObj, SLOT(unregisterShip(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(shipMovement(std::shared_ptr<Common::Ship>, Common::Point, Common::Point)),
            drawManagerObj, SLOT(changeShipPosition(std::shared_ptr<Common::Ship>, Common::Point, Common::Point)));
    connect(eventHandlerObj, SIGNAL(shipChangedLocation(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)),
            drawManagerObj, SLOT(changeShipPosition(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)));

    connect(userEventHandlerObj, SIGNAL(playerMovedInSS(QGraphicsPixmapItem*,int, int)),
            drawManagerObj, SLOT(changeShipUiPosition(QGraphicsPixmapItem*,int, int)));
    connect(userEventHandlerObj, SIGNAL(tradeRequest()), this, SLOT(pressedSpace()));
    connect(questionObj, SIGNAL(allQuestionsDone()),
            this, SLOT(allQuestionsDone()));
    connect(questionObj, SIGNAL(questionCompleted()),
            this, SLOT(questionCompleted()));

    connect(eventHandlerObj, SIGNAL(shipCallForHelp(std::shared_ptr<Common::Ship>)),
            this, SLOT(shipCallingForHelp(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(shipWasSaved(std::shared_ptr<Common::Ship>)),
            this, SLOT(shipSavedFromDistress(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(shipWasAbandoned(std::shared_ptr<Common::Ship>)),
            this, SLOT(shipAbandoned(std::shared_ptr<Common::Ship>)));

    connect(eventHandlerObj, SIGNAL(exceptionInShipExecution(std::shared_ptr<Common::Ship>, std::string const&)),
            this, SLOT(exceptionInShipExecution(std::shared_ptr<Common::Ship>, std::string const&)));


    Common::addNewShipType("Planet", [=] (std::shared_ptr<Common::StarSystem> initialLocation,
                                                        std::shared_ptr<Common::IEventHandler> events
                                                        ) -> std::shared_ptr<Common::Ship>  {
        return std::make_shared<Student::Planet>(std::make_shared<Student::PlanetCoreDrive>(galaxy_), initialLocation, events,
                                                 itemsInGalaxy_->getRandomTradeGoods());
    });

    ui->pbShowMap->setEnabled(false);
    ui->pbQuestions->setEnabled(false);
    ui->pbEndGame->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete refreshTimer_;
    delete gameTimer_;
    delete collisionTimer_;
    delete map_;
    delete statsWindow_;
    delete ui;
}



void MainWindow::startGame()
{
    assert(drawManager_);
    assert(galaxy_);
    assert(gameRunner_);
    assert(question_);

    ui->pbNewGame->setEnabled(false);

    QString nickName;
    bool ok;
    do{
        ok = false;
        nickName = QInputDialog::getText(this, tr("Enter nickname"),
                                              tr("Nickname:"), QLineEdit::Normal,
                                              "", &ok);
        ok = (!ok || !isNameCorrect(nickName));
    }while(ok);

    playerName_ = nickName;

    drawManager_->clearScene();
    galaxy_->removeShips();

    qDebug() << "New game";

    // Add player to the galaxy, must be called before travelToStarSystem
    createPlayer();

    // Add scene to the view
    ui->graphicsView->setScene(drawManager_->getScene());

    // Add enemies to the galaxy
    gameRunner_->spawnShips(500);

    question_->generateQuestions();

    // Set timers
    refreshTimer_ = new QTimer();
    connect(refreshTimer_, &QTimer::timeout, this, &MainWindow::refreshUI);
    refreshTimer_->start(5);

    collisionTimer_ = new QTimer();
    connect(collisionTimer_, &QTimer::timeout, this, &MainWindow::checkCollision);
    collisionTimer_->start(500);

    gameTimer_ = new QTimer();
    connect(gameTimer_, &QTimer::timeout, this, &MainWindow::gameEvent);
    gameTimer_->start(6000);

    // Start location is player's location
    travelToStarSystem(player_->getLocation()->getId());

    ui->lbCntStarSystems->setText(QString::number(galaxy_->getStarSystemVector().size()));

    ui->pbShowMap->setEnabled(true);
    ui->pbQuestions->setEnabled(true);
    ui->pbEndGame->setEnabled(true);

    loadSettings();
    initMap();

    playingTime_ = new QTime();
    playingTime_->start();

}

void MainWindow::createPlayer()
{
    assert(galaxy_);
    assert(settings_);
    assert(handler_);

    std::shared_ptr<Common::ShipEngine> shipEngine = std::make_shared<Common::WormHoleDrive>(galaxy_);
    std::shared_ptr<Common::StarSystem> initialLocation = galaxy_->getRandomSystem();
    Student::Statistics *stats = new Student::Statistics(settings_->getMaxCreditAllowance(), std::dynamic_pointer_cast<Student::EventHandler>(handler_));
    player_ = std::make_shared<Student::PlayerShip>(shipEngine, initialLocation, handler_, stats);
    player_->getStatistics()->addCredits(settings_->getInitialPlayerCredit());
    galaxy_->addShip(player_);
    handler_->shipSpawned(player_);
}

void MainWindow::pressedSpace()
{
    assert(player_);    
    assert(currentStarSystem_);
    assert(question_);
    assert(settings_);

    if(isPlayerTrading_ && !isNPCShipNear_)
    {
        assert(currentPlanet_);
        QStringList items;
        items << tr("Buy") << tr("Sell");
        bool ok;

        QString item = QInputDialog::getItem(this, tr("Trading"),
                                             tr("Trade type:"), items, 0, false, &ok);
        if (ok && !item.isEmpty())
        {
            Student::TradeAction trade = Student::TradeAction(player_, currentPlanet_, item.toLower().toStdString(),
                                            currentStarSystem_, question_, settings_);
            if(trade.canDo())
            {
                trade.execute();
            }
            else
            {
                showDialog("Trade action cannot be done!", false);
            }
        }
    }
    else if(isNPCShipNear_)
    {
        assert(currentNPCShip_);
        Common::RepairAction *action = new Common::RepairAction(player_, currentNPCShip_->getEngine(), false);
        int originHealth = currentNPCShip_->getEngine()->getHealth();
        if(originHealth == 0 && currentNPCShip_->isAbandoned())
        {
            return;
        }
        if(action->execute())
        {
            if(originHealth != currentNPCShip_->getEngine()->getHealth())
            {
                player_->getStatistics()->addCredits(Common::randomMinMax(1,2));
            }
        }
    }
}

void MainWindow::travelToStarSystem(unsigned starSystemId)
{
    assert(player_);
    assert(drawManager_);
    assert(galaxy_);
    assert(gameTimer_);

    if(map_ != nullptr)
    {
        gameTimer_->stop();
        map_->hide();
        ui->graphicsView->setFocus();
        if(player_->getLocation()->getId() == starSystemId)     // if destination is equal to current star system
        {
            gameTimer_->start();
            return;
        }
    }

    //Remove everything from scene
    drawManager_->clearScene();

    std::shared_ptr<Common::StarSystem> starSystem = galaxy_->getStarSystemById(starSystemId);

    if(starSystem == nullptr) {
        throw Student::UnknownStarSystemException("Star system does not exist in the galaxy.");
    }

    currentStarSystem_ = starSystem;

    //Set player's new location
    player_->setLocation(starSystem);

    for(auto ship : galaxy_->getShipsInStarSystem(starSystem->getName()))
    {
        try
        {
            drawManager_->drawShip(ship);
        }
        catch (Student::UnknownShipException ex)
        {
            showErrorDialog(ex.msg(), true);
        }
    }

    ui->lbSSEnemies->setText(QString::number(drawManager_->getNumberOfShips()));

    const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None" };
    ui->lbSSName->setText(starSystem->getName().data());
    ui->lbSSEconomy->setText(economy[starSystem->getEconomy()]);
    ui->lbSSPopulation->setText(QString::number(starSystem->getPopulation()));
    try
    {
        drawManager_->setFocusOnPlayer(player_);
    }
    catch(Student::UnknownShipException ex)
    {
        showErrorDialog(ex.msg(), true);
    }
    ui->graphicsView->setFocus();
    if(map_ != nullptr)
    {
        gameTimer_->start();
    }
}

void MainWindow::refreshUI()
{
    assert(drawManager_);
    assert(player_);

    ui->graphicsView->centerOn(drawManager_->getPlayerShipUiByObject(player_));
    try
    {
        drawManager_->setFocusOnPlayer(player_);
    }
    catch(Student::UnknownShipException ex)
    {
        showErrorDialog(ex.msg(), true);
    }
    ui->ptPlayerInventory->clear();
    QString inventory = "";
    for(auto k : player_->getInventory())
    {
        inventory += QString(k.getName().data()) + " : " + QString::number(k.getPrice()) + "\n";
    }
    ui->ptPlayerInventory->appendPlainText(inventory);
    ui->lbCredits->setText(QString::number(player_->getStatistics()->getCreditBalance()));


    if(statsWindow_ != nullptr && player_ != nullptr)
    {
        statsWindow_->fillStatistics(player_->getStatistics());
    }
}

void MainWindow::gameEvent()
{
    assert(gameRunner_);

    gameRunner_->createActions();
    gameRunner_->doActions();
}

void MainWindow::checkCollision()
{
    assert(drawManager_);
    assert(player_);

    QList<QGraphicsItem *> colliding_Items = drawManager_->getScene()->collidingItems(drawManager_->getPlayerShipUiByObject(player_));
    for(int i = 0, n = colliding_Items.size(); i<n; ++i)
    {
        if(typeid (*(colliding_Items[i])) == typeid (Ui::NPCShipUi))
        {
            isNPCShipNear_ = true;
            ui->gbStarPlanet->setTitle("NPC Ship");
            ui->detailNearbyTitle->setText(QString("Health:"));
            ui->nameNearbyTitle->setText(QString("Name:"));
            std::shared_ptr<Common::Ship> ship = drawManager_->getCargoShipByUiItem(colliding_Items[i]);
            currentNPCShip_ = ship;
            ui->lbSPName->setText(QString::fromStdString(ship->getName()));
            std::string hp = std::to_string(ship->getEngine()->getHealth()) + " / " +
                     std::to_string(ship->getEngine()->getMaxHealth());
            ui->lbSPGoods->setText(QString::fromStdString(hp));
            return;
        }
        else if(typeid (*(colliding_Items[i])) == typeid (Ui::PlanetUi))
        {
            isPlayerTrading_ = true;
            ui->gbStarPlanet->setTitle("Star Planet");
            ui->detailNearbyTitle->setText(QString("Goods:"));
            ui->nameNearbyTitle->setText(QString("Name:"));
            std::shared_ptr<Student::Planet> planet = drawManager_->getPlanetByUiItem(colliding_Items[i]);
            ui->lbSPName->setText(QString::fromStdString(planet->getName()));
            ui->lbSPGoods->setText(QString::fromStdString(planet->getGoods().getName()));
            currentPlanet_ = planet;
            return;
        }
    }

    isPlayerTrading_ = false;
    isNPCShipNear_ = false;
    ui->lbSPName->clear();
    ui->lbSPGoods->clear();
    ui->gbStarPlanet->setTitle("Nothing nearby");
    ui->detailNearbyTitle->clear();
    ui->nameNearbyTitle->clear();
}

void MainWindow::initMap()
{
    QObject* eventHandlerObj = dynamic_cast<QObject*>(userActionHandler_.get());
    connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)),
            this, SLOT(travelToStarSystem(unsigned)));
    map_ = new MapWindow(userActionHandler_, galaxy_->getStarSystemVector(), player_->getLocation(), this);
    connect(eventHandlerObj, SIGNAL(showGoodsInfo(unsigned)),
            map_, SLOT(showGoodsInfo(unsigned)));
    connect(map_, SIGNAL(planetsByStarSystemRequest(unsigned)),
            this, SLOT(planetsInStarSystemRequest(unsigned)));
    connect(map_, SIGNAL(finished(int)),
            this, SLOT(changeFocus()));
    map_->setModal(true);

    markQuestionStarSystems();
}

void MainWindow::loadSettings()
{
    assert(topListWindow_);

    topListWindow_->loadSettings();
}

void MainWindow::saveSettings()
{
    assert(topListWindow_);

    topListWindow_->saveSettings(playerName_, player_->getStatistics()->getPlayerStat());
}

void MainWindow::on_pbNewGame_clicked()
{
    startGame();
}

void MainWindow::on_actionNew_Game_triggered()
{
    startGame();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QTextEdit* help = new QTextEdit();
    help->setWindowIcon(QIcon(":/images/images/favicon.png"));
    help->setWindowFlags(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->resize(384, 256);
    help->append(tr("<h1>About</h1>Welcome to Semicolon Spaceship game."
                 "<br/>Lucia Kuchárová & Andrej Vlasatý"
                 "<br/><br/>Player, as a hero of whole Galaxy, is supposed to save ships, which are in some kind of trouble, "
                 "by repairing their engines. Player travels among Star Systems and searches for broken ships. "
                 "In addition, player can trade with planets in every Star System and fulfill Questions, "
                 "which are requests from certain planets to obtain certain goods."
                 "<br/><br/>Hope you like it."));
    help->show();
}

void MainWindow::on_actionHelp_triggered()
{
    QTextEdit* help = new QTextEdit();
    help->setWindowIcon(QIcon(":/images/images/favicon.png"));
    help->setWindowFlags(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->resize(384, 256);
    help->append(tr("<h1>Help</h1>Use key arrows to move."
                 "<br/>Fly over the planet and press space to trade with the planet."
                 "<br/>Ship is being repaired by hitting space."
                 "<br/><br/>Player can move in Star System view using up, down, left and right arrow keys. "
                 "When player ship reaches planet or ship, clicking on spacebar key starts interaction between them. "
                 "Any other interaction with game is done by mouse clicks."
                 "<br/>Hope you like it."));
    help->show();
}

void MainWindow::planetsInStarSystemRequest(unsigned id)
{
    assert(galaxy_);
    assert(drawManager_);
    assert(map_);

    std::shared_ptr<Common::StarSystem> starSystem = galaxy_->getStarSystemById(id);
    Common::IGalaxy::ShipVector ships = galaxy_->getShipsInStarSystem(starSystem->getName());
    Common::IGalaxy::ShipVector planets = drawManager_->getPlanetsByStarSystem(ships);
    map_->setPlanetsByStarSystem(planets);
}

void MainWindow::shipCallingForHelp(std::shared_ptr<Common::Ship> ship)
{
    assert(drawManager_);

    //add ship to distress list
    shipsInDistress_.push_back(ship);
    //Stop ship in ui
    Ui::NPCShipUi* shipUi = drawManager_->getShipUiByObject(ship);
    if(shipUi != nullptr)
    {
        shipUi->canMove(false);
    }
    else
    {
        throw Student::UnknownShipException("NPC ship " + ship->getName() + " was not found in UI");
    }
    //Update ui
    ui->lbShipsInDistress->setText(QString::number(shipsInDistress_.size()));

    if(map_ != nullptr)
    {
        try
        {
            map_->markStarSystemAsDistressed(ship->getLocation());
        }
        catch(Student::UnknownStarSystemException ex)
        {
            showErrorDialog(ex.msg(), true);
        }
    }
}

void MainWindow::shipSavedFromDistress(std::shared_ptr<Common::Ship> ship)
{
    assert(drawManager_);
    assert(player_);

    qDebug() << "Ship moving again!";
    bool isStarSystemFullySaved = true;

    //remove ship from distress list
    for(unsigned i = 0; i < shipsInDistress_.size(); i++)
    {
        if(shipsInDistress_[i] == ship)
        {
            shipsInDistress_.erase(shipsInDistress_.begin()+i);
            continue;
        }

        if(shipsInDistress_[i]->getLocation() == ship->getLocation())
        {
            isStarSystemFullySaved = false;
        }
    }
    //Ship in ui can move again
    Ui::NPCShipUi* shipUi  = drawManager_->getShipUiByObject(ship);
    if(shipUi != nullptr)
    {
        shipUi->canMove(true);
    }
    else
    {
        throw Student::UnknownShipException("NPC ship " + ship->getName() + " was not found in UI");
    }
    //Update ui
    ui->lbShipsInDistress->setText(QString::number(shipsInDistress_.size()));

    if(isStarSystemFullySaved && map_ != nullptr)
    {
        try
        {
            map_->unmarkStarSystemDistress(ship->getLocation());
        }
        catch(Student::UnknownStarSystemException ex)
        {
            showErrorDialog(ex.msg(), true);
        }
    }
    //update statistics
    player_->getStatistics()->addPoints(settings_->getPointsFromSaving());
    player_->getStatistics()->addCredits(settings_->getCreditsFromSaving());
    player_->getStatistics()->addSavedShip();
}

void MainWindow::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    assert(drawManager_);
    assert(map_);
    assert(player_);

    bool isStarSystemFreeOfDistress = true;
    //set grave icon
    try
    {
        drawManager_->shipIsAbandoned(ship);
    }
    catch(Student::UnknownShipException ex)
    {
        showErrorDialog(ex.msg(), true);
    }
    //remove ship from distress list
    for(unsigned i = 0; i < shipsInDistress_.size(); i++)
    {
        if(shipsInDistress_[i] == ship)
        {
            shipsInDistress_.erase(shipsInDistress_.begin()+i);
            continue;
        }

        if(shipsInDistress_[i]->getLocation() == ship->getLocation())
        {
            isStarSystemFreeOfDistress = false;
        }
    }
    //Update ui
    ui->lbShipsInDistress->setText(QString::number(shipsInDistress_.size()));

    if(isStarSystemFreeOfDistress && map_ != nullptr)
    {
        try
        {
            map_->unmarkStarSystemDistress(ship->getLocation());
        }
        catch(Student::UnknownStarSystemException ex)
        {
            showErrorDialog(ex.msg(), true);
        }
    }
    //update statistics
    player_->getStatistics()->addLostShip();
}

void MainWindow::exceptionInShipExecution(std::shared_ptr<Common::Ship> ship, const std::string &msg)
{
    showDialog("Problem with ship " + ship->getName() + ": " + msg, true);
}

void MainWindow::on_actionMy_statistics_triggered()
{
    //Check if player is initialized
    if(player_ != nullptr)
    {
        if(statsWindow_ == nullptr)
        {
            statsWindow_ = new StatisticsWindow(player_->getStatistics(), playerName_);
            QObject* eventHandlerObj = dynamic_cast<QObject*>(handler_.get());
            connect(eventHandlerObj, SIGNAL(statisticsNeedUpdate(bool)),
                    statsWindow_, SLOT(setNeedForUpdate(bool)));
            statsWindow_->setModal(true);
            statsWindow_->exec();
        }
        else
        {
            statsWindow_->show();
        }
    }
    else
    {
        showDialog("No statistics at the moment, game haven't started yet!", false);
    }
}

void MainWindow::on_pbShowMap_clicked()
{
    assert(userActionHandler_);
    assert(galaxy_);
    assert(player_);

    if(map_ == nullptr)
    {
        initMap();
        map_->exec();
    }
    else
    {
        markQuestionStarSystems();
        map_->show();
    }
    map_->centerOnPlayer();
}

void MainWindow::markQuestionStarSystems()
{
    assert(map_);
    assert(question_);
    assert(galaxy_);

    QList<questions_t> active = question_->getActiveQuestions();
    for(auto element : active)
    {
        map_->markQuestionStarSystem(galaxy_->getStarSystemByName(element.second.first));
    }
}

void MainWindow::on_pbEndGame_clicked()
{
    assert(drawManager_);
    assert(galaxy_);
    assert(refreshTimer_);
    assert(collisionTimer_);
    assert(gameTimer_);

    refreshTimer_->stop();
    collisionTimer_->stop();
    gameTimer_->stop();

    ui->pbNewGame->setEnabled(true);
    ui->pbEndGame->setEnabled(false);
    ui->pbQuestions->setEnabled(false);
    ui->pbShowMap->setEnabled(false);
    ui->pbShowMap->setEnabled(false);

    ui->lbCntStarSystems->setText("0");
    ui->lbShipsInDistress->setText("0");
    ui->lbSSName->clear();
    ui->lbSSEconomy->clear();
    ui->lbSSPopulation->clear();
    ui->lbSSEnemies->clear();
    ui->lbCredits->clear();

    saveSettings();

    drawManager_->clearScene();
    galaxy_->removeShips();

    player_ = nullptr;
    map_ = nullptr;
}

void MainWindow::on_actionTop_list_triggered()
{
    assert(topListWindow_);

    topListWindow_->setModal(true);
    topListWindow_->show();
}

void MainWindow::on_actionDefault_Settings_triggered()
{
    assert(settings_);

    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));
    msgBox.setText("Do you want to set default settings?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes)
    {
        settings_->setDefault();
    }

}

void MainWindow::on_actionReset_top_list_triggered()
{
    assert(topListWindow_);

    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));
    msgBox.setText("Do you want to reset top list?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes)
    {
        topListWindow_->resetStats();
    }
}

void MainWindow::changeFocus()
{
    ui->graphicsView->setFocus();
}


void MainWindow::on_pbQuestions_clicked()
{
    assert(question_);

    questionDlg_ = new QuestionDlg(question_->getActiveQuestions(), question_->getCompletedQuestions(), this);
    connect(questionDlg_, SIGNAL(finished(int)),
            this, SLOT(changeFocus()));
    questionDlg_->setAttribute(Qt::WA_DeleteOnClose, true);
    questionDlg_->setModal(true);
    questionDlg_->exec();
}

void MainWindow::allQuestionsDone()
{
    assert(playingTime_);

    int playingTime = playingTime_->elapsed();
    showDialog("Congratulation! You finished all questions. Your time is " + std::to_string(playingTime/1000) + "s", false);
}

void MainWindow::questionCompleted()
{
    assert(player_);
    assert(settings_);

    player_->getStatistics()->addCompletedQuest();
    player_->getStatistics()->addPoints(settings_->getPointsFromQuestion());
}

bool MainWindow::isNameCorrect(QString name)
{
    name = name.trimmed();
    int count = name.count(QRegExp("[!@#$%^&()_+]"));
    if(name.length() > 0 && name.length() < 10 && count == 0)
    {
        return true;
    }
    return false;
}

void MainWindow::showDialog(std::string msg, bool quitProgram)
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));

    if(quitProgram)
    {
        msgBox.setText(QString::fromStdString(msg));
    }
    else
    {
        msgBox.setText(QString::fromStdString(msg));
    }

    msgBox.exec();

    if(quitProgram)
    {
        exit(1);
    }
}

void MainWindow::showErrorDialog(std::string msg, bool quitProgram)
{
    if(quitProgram)
    {
        showDialog("Error occured! Program has to be terminated. Reason: " + msg, quitProgram);
    }
    else
    {
        showDialog("Error occured! Reason: " + msg, quitProgram);
    }
}


