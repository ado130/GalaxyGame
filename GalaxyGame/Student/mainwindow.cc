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

#include <QDebug>
#include <QTextEdit>
#include <QTimer>
#include <QBrush>
#include <QInputDialog>
#include <QSettings>
#include <QtConcurrent>
#include <QFuture>
#include <QMessageBox>



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
    drawManager_ = std::make_shared<Student::DrawableObjectsManager>(new Student::StarSystemScene(this), userActionHandler_);
    itemsInGalaxy_ = std::make_shared<ItemsInGalaxy>();
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

    Common::addNewShipType("Planet", [=] (std::shared_ptr<Common::StarSystem> initialLocation,
                                                        std::shared_ptr<Common::IEventHandler> events
                                                        ) -> std::shared_ptr<Common::Ship>  {
        return std::make_shared<Student::Planet>(std::make_shared<PlanetCoreDrive>(galaxy_), initialLocation, events,
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

    // Start location is player's location
    travelToStarSystem(player_->getLocation()->getId());

    // Set timers
    refreshTimer_ = new QTimer();
    connect(refreshTimer_, &QTimer::timeout, this, &MainWindow::refreshUI);
    refreshTimer_->start(5);

    collisionTimer_ = new QTimer();
    connect(collisionTimer_, &QTimer::timeout, this, &MainWindow::checkCollision);
    collisionTimer_->start(500);

    gameTimer_ = new QTimer();
    connect(gameTimer_, &QTimer::timeout, this, &MainWindow::gameEvent);
    gameTimer_->start(10000);

    ui->lbCntStarSystems->setText(QString::number(galaxy_->getStarSystemVector().size()));


    ui->pbShowMap->setEnabled(true);
    ui->pbQuestions->setEnabled(true);
    ui->pbEndGame->setEnabled(true);

    loadSettings();

    playingTime_ = new QTime();
    playingTime_->start();

}

void MainWindow::createPlayer()
{
    std::shared_ptr<Common::ShipEngine> shipEngine = std::make_shared<Common::WormHoleDrive>(galaxy_);
    std::shared_ptr<Common::StarSystem> initialLocation = galaxy_->getRandomSystem();
    Student::Statistics *stats = new Student::Statistics(settings_->getMaxCreditAllowance(), std::dynamic_pointer_cast<Student::EventHandler>(handler_));
    player_ = std::make_shared<PlayerShip>(shipEngine, initialLocation, handler_, stats);
    player_->getStatistics()->addCredits(settings_->getInitialPlayerCredit());
    galaxy_->addShip(player_);
    handler_->shipSpawned(player_);
}

void MainWindow::pressedSpace()
{
    if(isPlayerTrading_ && !isNPCShipNear_)
    {
        QStringList items;
        items << tr("Buy") << tr("Sell");
        bool ok;

        QString item = QInputDialog::getItem(this, tr("Trading"),
                                             tr("Trade type:"), items, 0, false, &ok);
        if (ok && !item.isEmpty())
        {
            TradeAction trade = TradeAction(player_, currentPlanet_, item.toLower().toStdString(),
                                            currentStarSystem_, question_, settings_);
            if(trade.canDo())
            {
                trade.execute();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("Trade action cannot be done!");
                msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));
                msgBox.exec();
            }
        }
    }
    else if(isNPCShipNear_)
    {
        qDebug() << "wanna repair!";
        Common::RepairAction *action = new Common::RepairAction(player_, currentNPCShip_->getEngine(), false);
        action->execute();
    }
}

void MainWindow::travelToStarSystem(unsigned starSystemId)
{

//    qDebug() << "location before: " << player_->getLocation()->getCoordinates().x << "," << player_->getLocation()->getCoordinates().y;
//    qDebug() << "health before: " << player_->getEngine()->getHealth();
//    qDebug() << "can start before: " << player_->getEngine()->canStart();

    if(map_ != nullptr)
    {
        gameTimer_->stop();
        map_->hide();
        if(player_->getLocation()->getId() == starSystemId)     // if destination is equal to current star system
        {
            gameTimer_->start();
            return;
        }
    }

    //Remove everything from scene
    drawManager_->clearScene();

    std::shared_ptr<Common::StarSystem> starSystem = galaxy_->getStarSystemById(starSystemId);

//    qDebug() << "location after: " << player_->getLocation()->getCoordinates().x << "," << player_->getLocation()->getCoordinates().y;
//    qDebug() << "health after: " << player_->getEngine()->getHealth();
//    qDebug() << "can start after: " << player_->getEngine()->canStart();

    if(starSystem == nullptr) {
        throw Common::ObjectNotFoundException("Star system does not exist in the galaxy.");
    }

    currentStarSystem_ = starSystem;

    //Set player's new location
    player_->setLocation(starSystem);

    for(auto ship : galaxy_->getShipsInStarSystem(starSystem->getName()))
    {
        drawManager_->drawShip(ship);
    }

    ui->lbSSEnemies->setText(QString::number(drawManager_->getNumberOfShips()));

    const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None" };
    ui->lbSSName->setText(starSystem->getName().data());
    ui->lbSSEconomy->setText(economy[starSystem->getEconomy()]);
    ui->lbSSPopulation->setText(QString::number(starSystem->getPopulation()));
    drawManager_->setFocusOnPlayer(player_);
    if(map_ != nullptr)
    {
        gameTimer_->start();
    }
}

void MainWindow::refreshUI()
{
    ui->graphicsView->centerOn(drawManager_->getPlayerShipUiByObject(player_));
    drawManager_->setFocusOnPlayer(player_);
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
    gameRunner_->createActions();
    gameRunner_->doActions();
}

void MainWindow::checkCollision()
{
    QList<QGraphicsItem *> colliding_Items = drawManager_->getScene()->collidingItems(drawManager_->getPlayerShipUiByObject(player_));
    for(int i = 0, n = colliding_Items.size(); i<n; ++i)
    {
        if(typeid (*(colliding_Items[i])) == typeid (NPCShipUi))
        {
            isNPCShipNear_ = true;
            std::shared_ptr<Common::Ship> ship = drawManager_->getCargoShiptByUiItem(colliding_Items[i]);
            currentNPCShip_ = ship;
            return;
        }
        else if(typeid (*(colliding_Items[i])) == typeid (Student::PlanetUi))
        {
            isPlayerTrading_ = true;
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
}

void MainWindow::loadSettings()
{
    topListWindow_->loadSettings();
}

void MainWindow::saveSettings()
{
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
                 "<br/> Hope you like it."));
    help->show();
}

void MainWindow::on_actionHelp_triggered()
{
    QTextEdit* help = new QTextEdit();
    help->setWindowIcon(QIcon(":/images/images/favicon.png"));
    help->setWindowFlags(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->resize(384, 256);
    help->append(tr("<h1>Help</h1>Use arrow keys to move."
                 "<br/>Fly over the planet and press space to trade with the planet."
                 "<br/>Hope you like it."));
    help->show();
}

void MainWindow::planetsInStarSystemRequest(unsigned id)
{
    std::shared_ptr<Common::StarSystem> starSystem = galaxy_->getStarSystemById(id);
    Common::IGalaxy::ShipVector ships = galaxy_->getShipsInStarSystem(starSystem->getName());
    Common::IGalaxy::ShipVector planets = drawManager_->getPlanetsByStarSystem(ships);
    map_->setPlanetsByStarSystem(planets);
}

void MainWindow::shipCallingForHelp(std::shared_ptr<Common::Ship> ship)
{
    //add ship to distress list
    shipsInDistress_.push_back(ship);
    //Stop ship in ui
    drawManager_->getCargoShipUiByObject(ship)->canMove(false);
    //Update ui
    ui->lbShipsInDistress->setText(QString::number(shipsInDistress_.size()));

    if(map_ != nullptr)
    {
        map_->markStarSystemAsDistressed(ship->getLocation());
    }
}

void MainWindow::shipSavedFromDistress(std::shared_ptr<Common::Ship> ship)
{
    qDebug() << "Ship moving again!";
    bool isStarSystemFullySaved = true;

    //remove ship from distress list
    for(int i = 0; i < shipsInDistress_.size(); i++)
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
    drawManager_->getCargoShipUiByObject(ship)->canMove(true);
    //Update ui
    ui->lbShipsInDistress->setText(QString::number(shipsInDistress_.size()));

    if(isStarSystemFullySaved && map_ != nullptr)
    {
        map_->unmarkStarSystemDistress(ship->getLocation());
    }
    //update statistics
    player_->getStatistics()->addPoints(settings_->getPointsFromSaving());
    player_->getStatistics()->addCredits(settings_->getCreditsFromSaving());
    player_->getStatistics()->addSavedShip();
}

void MainWindow::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    bool isStarSystemFreeOfDistress = true;
    //set grave icon
    drawManager_->shipIsAbandoned(ship);

    //remove ship from distress list
    for(int i = 0; i < shipsInDistress_.size(); i++)
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
        map_->unmarkStarSystemDistress(ship->getLocation());
    }
    //update statistics
    player_->getStatistics()->addLostShip();
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
        QMessageBox msgBox;
        msgBox.setText("No statistics at the moment, game haven't started yet!");
        msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));
        msgBox.exec();
    }
}

void MainWindow::on_pbShowMap_clicked()
{
    if(map_ == nullptr)
    {
        QObject* eventHandlerObj = dynamic_cast<QObject*>(userActionHandler_.get());
        connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)),
                this, SLOT(travelToStarSystem(unsigned)));
        map_ = new MapWindow(userActionHandler_, galaxy_->getStarSystemVector(), player_->getLocation(), this);
        connect(eventHandlerObj, SIGNAL(showGoodsInfo(unsigned)),
                map_, SLOT(showGoodsInfo(unsigned)));
        connect(map_, SIGNAL(planetsByStarSystemRequest(unsigned)),
                this, SLOT(planetsInStarSystemRequest(unsigned)));
        map_->setModal(true);
        map_->exec();
    }
    else
    {
        map_->show();
    }
}

void MainWindow::on_pbEndGame_clicked()
{
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
    topListWindow_->setModal(true);
    topListWindow_->show();
}

void MainWindow::on_actionDefault_Settings_triggered()
{
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


void MainWindow::on_pbQuestions_clicked()
{
    questionDlg_ = new QuestionDlg(question_->activeQuestions(), question_->completedQuestions(), this);
    questionDlg_->setAttribute(Qt::WA_DeleteOnClose, true);
    questionDlg_->setModal(true);
    questionDlg_->exec();
}

void MainWindow::allQuestionsDone()
{
    int playingTime = playingTime_->elapsed();
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));
    msgBox.setText("Congratulation! You finished all questions. Your time is " + QString::number(playingTime/1000) + "s");
    msgBox.exec();
}

void MainWindow::questionCompleted()
{
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


