#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "initialize.hh"
#include "planet.hh"
#include "playershipui.hh"
#include "wormholedrive.hh"
#include "objectnotfoundexception.hh"
#include "statisticswindow.hh"
#include "playership.hh"

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
//    NOTE: MAYBE this userActionHandler will be deleted, if we can send signals FROM UI via their eventHandler
    userActionHandler_ = std::make_shared<Student::UserActionHandler>();
    drawManager_ = std::make_shared<Student::DrawableObjectsManager>(new Student::StarSystemScene(this));
    itemsInGalaxy_ = std::make_shared<ItemsInGalaxy>();
    question_ = std::make_shared<Student::Question>(galaxy, itemsInGalaxy_);

    QObject* eventHandlerObj = dynamic_cast<QObject*>(handler.get());
    QObject* drawManagerObj = dynamic_cast<QObject*>(drawManager_.get());
    QObject* questionObj = dynamic_cast<QObject*>(question_.get());
    connect(eventHandlerObj, SIGNAL(registerShipToUi(std::shared_ptr<Common::Ship>)),
            drawManagerObj, SLOT(registerShip(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(unregisterShipFromUi(std::shared_ptr<Common::Ship>)),
            drawManagerObj, SLOT(unregisterShip(std::shared_ptr<Common::Ship>)));
    connect(drawManagerObj, SIGNAL(pressedSpaceSignal()), this, SLOT(pressedSpace()));
    connect(eventHandlerObj, SIGNAL(shipMovement(std::shared_ptr<Common::Ship>, int, int)),
            this, SLOT(shipMovement(std::shared_ptr<Common::Ship>, int, int)));
    connect(questionObj, SIGNAL(allQuestionsDone()),
            this, SLOT(allQuestionsDone()));

//    Todo: every ship has to be able to change it's location --> change function travelToStarSystem
//    connect(eventHandlerObj, SIGNAL(changeShipLocationBetweenStarSystems(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)),
//            this, SLOT(travelToStarSystem(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)));

    Common::addNewShipType("Planet", [=] (std::shared_ptr<Common::StarSystem> initialLocation,
                                                        std::shared_ptr<Common::IEventHandler> events
                                                        ) -> std::shared_ptr<Common::Ship>  {
        return std::make_shared<Student::Planet>(std::make_shared<PlanetCoreDrive>(galaxy_), initialLocation, events,
                                                 itemsInGalaxy_->getRandomTradeGoods());
    });

    ui->pbShowMap->setEnabled(false);
    ui->pbQuestions->setEnabled(false);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete refreshTimer_;
    delete gameTimer_;
    delete collisionTimer_;
    delete map_;
    delete ui;
}

void MainWindow::startGame()
{
    ui->pbNewGame->setEnabled(false);
    // ToDo: do not ignore ToDo's
    //bool ok;
    //QString nickName = QInputDialog::getText(this, tr("Enter nickname"),
    //                                      tr("Nickname:"), QLineEdit::Normal,
    //                                      "", &ok);

    drawManager_->clearScene();
    galaxy_->removeShips();

    qDebug() << "New game";

    // Add player to the galaxy, must be called before travelToStarSystem
    createPlayer();

    // Add enemies to the galaxy
    gameRunner_->spawnShips(300);

    question_->generateQuestions();

    // Start location is player's location
    travelToStarSystem(player_->getLocation()->getId());

    // Add scene to the view
    ui->graphicsView->setScene(drawManager_->getScene());
    drawManager_->setFocusOnPlayer(player_);

    // Set timers
    refreshTimer_ = new QTimer();
    connect(refreshTimer_, &QTimer::timeout, this, &MainWindow::refreshUI);
    refreshTimer_->start(5);

    collisionTimer_ = new QTimer();
    connect(collisionTimer_, &QTimer::timeout, this, &MainWindow::checkCollision);
    collisionTimer_->start(500);

    gameTimer_ = new QTimer();
    connect(gameTimer_, &QTimer::timeout, this, &MainWindow::gameEvent);
    gameTimer_->start(2000);

    ui->lbCntStarSystems->setText(QString::number(galaxy_->getStarSystemVector().size()));
    //NOTE: galaxy has only vector if ships in it -> we can have more shipTypes and we would have to check
    //every type it it is "enemy" type or not ... also, our playership is in this vector too, so lblCntEnemies
    //is basically --"lbCntAllCargoShipsAndPlanetsAndPlayership and every future type of ship not yet invented"--
//    ui->lbCntEnemies

    ui->pbShowMap->setEnabled(true);
    ui->pbNewGame->setEnabled(true);
    ui->pbQuestions->setEnabled(true);

    playingTime_ = new QTime();
    playingTime_->start();
}

void MainWindow::createPlayer()
{
    std::shared_ptr<Common::ShipEngine> shipEngine = std::make_shared<Common::WormHoleDrive>(galaxy_);
    std::shared_ptr<Common::StarSystem> initialLocation = galaxy_->getRandomSystem();//std::make_shared<Common::StarSystem>("Earth", Common::StarSystem::Colony, 0, 10000, Common::Point(0, 0));
    player_ = std::make_shared<PlayerShip>(shipEngine, initialLocation, handler_);
    galaxy_->addShip(player_);
    handler_->shipSpawned(player_);

//    ToDo: check connection to EventHandler and how to use it for emiting signals FROM UI
//    QObject* eventHandlerObj = dynamic_cast<QObject*>(userActionHandler_.get());
//    connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)), this, SLOT(travelToStarSystem(unsigned)));
//    connect(player_.get(), SIGNAL(pressedSpace()), this, SLOT(pressedSpace));
}

void MainWindow::pressedSpace()
{
    if(isPlayerTrading_)
    {
        QStringList items;
        items << tr("Buy") << tr("Sell");
        bool ok;

        QString item = QInputDialog::getItem(this, tr("Trading"),
                                             tr("Trade type:"), items, 0, false, &ok);
        if (ok && !item.isEmpty())
        {
            if(item.toLower() == "buy")
            {
                if(player_->getInventory().size() < MAX_PLAYER_INVENTORY)
                {
                    for(auto k : player_->getInventory())
                    {
                        if(currentPlanet_->getGoods().getName() == k.getName() && currentPlanet_->getGoods().getPrice() == k.getPrice())
                        {
                            return;
                        }
                    }

                    player_->addGoodsToInventory(currentPlanet_->getGoods());
                }
            }
            else if(item.toLower() == "sell")
            {
                for(auto k : player_->getInventory())
                {
                    bool correct = question_->checkQuestion(currentStarSystem_->getName(), currentPlanet_->getName(), k.getName());
                    if(correct)
                    {
                        player_->removeGoodsFromInventory(k.getName());
                        return;
                    }
                }
            }
        }
    }
}

void MainWindow::travelToStarSystem(unsigned starSystemId)
{
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

    if(starSystem == nullptr)
    {
        throw Common::ObjectNotFoundException("Star system does not exist in the galaxy.");
    }

    currentStarSystem_ = starSystem;

    //Set player's new location
    player_->setLocation(starSystem);

    for(auto ship : galaxy_->getShipsInStarSystem(starSystem->getName()))
    {
        drawManager_->drawShip(ship);
    }

    qDebug() << drawManager_->getNumberOfShips();
    ui->lbSSEnemies->setText(QString::number(drawManager_->getNumberOfShips()));

    const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None" };
    ui->lbSSName->setText(starSystem->getName().data());
    ui->lbSSEconomy->setText(economy[starSystem->getEconomy()]);
    ui->lbSSPopulation->setText(QString::number(starSystem->getPopulation()));
    ui->lbSSCoordinates->setText("x: " + QString::number(starSystem->getCoordinates().x*50) +
                                 " y: " + QString::number(starSystem->getCoordinates().y*50));
    drawManager_->setFocusOnPlayer(player_);
    if(map_ != nullptr)
    {
        gameTimer_->start();
    }
}

void MainWindow::shipMovement(std::shared_ptr<Common::Ship> ship, int diffX, int diffY)
{
//    QGraphicsItem* item = scene_->getSceneShip(ship);
//    if(item != nullptr)
//    {
//        item->setPos(item->x() + diffX, item->y() + diffY);
//    }
}

void MainWindow::refreshUI()
{
    ui->graphicsView->centerOn(drawManager_->getPlayerShipUiByObject(player_));
    ui->ptPlayerInventory->clear();
    QString inventory = "";
    for(auto k : player_->getInventory())
    {
        inventory += QString(k.getName().data()) + " : " + QString::number(k.getPrice()) + "\n";
    }
    ui->ptPlayerInventory->appendPlainText(inventory);
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
            // ToDo: collision with NPC ship
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
    ui->lbSPName->clear();
    ui->lbSPGoods->clear();
}

void MainWindow::loadSettings()
{

}

void MainWindow::saveSettings()
{

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
    help->setWindowFlags(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->resize(384, 256);
    help->append(tr("<h1>Help</h1>Use arrow keys to move."
                 "<br/>Fly over the planet and press space to trade with the planet."
                 "<br/>Hope you like it."));
    help->show();
}

void MainWindow::on_actionMy_statistics_triggered()
{
    //Check if player is initialized
    if(player_ != nullptr)
    {
        StatisticsWindow* stats = new StatisticsWindow(player_);
        stats->setModal(true);
        stats->exec();
        delete stats;
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
        map_ = new MapWindow(userActionHandler_, galaxy_->getStarSystemVector(), this);
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

void MainWindow::planetsInStarSystemRequest(unsigned id)
{
    std::shared_ptr<Common::StarSystem> starSystem = galaxy_->getStarSystemById(id);
    Common::IGalaxy::ShipVector ships = galaxy_->getShipsInStarSystem(starSystem->getName());
    Common::IGalaxy::ShipVector planets = drawManager_->getPlanetsByStarSystem(ships);
    map_->setPlanetsByStarSystem(planets);
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
    msgBox.setText("Congratulation! Your time is " + QString::number(playingTime/1000) + "s");
    msgBox.exec();
}
