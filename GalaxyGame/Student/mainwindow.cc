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

    QObject* eventHandlerObj = dynamic_cast<QObject*>(handler.get());
    QObject* drawManagerObj = dynamic_cast<QObject*>(drawManager_.get());
    connect(eventHandlerObj, SIGNAL(registerShipToUi(std::shared_ptr<Common::Ship>)),
            drawManagerObj, SLOT(registerShip(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(unregisterShipFromUi(std::shared_ptr<Common::Ship>)),
            drawManagerObj, SLOT(unregisterShip(std::shared_ptr<Common::Ship>)));
    connect(eventHandlerObj, SIGNAL(shipMovement(std::shared_ptr<Common::Ship>, Common::Point, Common::Point)),
            drawManagerObj, SLOT(changeShipPosition(std::shared_ptr<Common::Ship>, Common::Point, Common::Point)));
    connect(eventHandlerObj, SIGNAL(shipChangedLocation(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)),
            drawManagerObj, SLOT(changeShipPosition(std::shared_ptr<Common::Ship>, std::shared_ptr<Common::StarSystem>)));



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

    // Add scene to the view
    ui->graphicsView->setScene(drawManager_->getScene());

    // Add enemies to the galaxy
    gameRunner_->spawnShips(500);

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
    //NOTE: galaxy has only vector if ships in it -> we can have more shipTypes and we would have to check
    //every type it it is "enemy" type or not ... also, our playership is in this vector too, so lblCntEnemies
    //is basically --"lbCntAllCargoShipsAndPlanetsAndPlayership and every future type of ship not yet invented"--
//    ui->lbCntEnemies

    ui->pbShowMap->setEnabled(true);
    ui->pbNewGame->setEnabled(true);
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
//    connect(player_, &PlayerShipUi::pressedSpace, this, &MainWindow::pressedSpace);
}

void MainWindow::pressedSpace()
{
    if(isPlayerTrading_)
    {
        // ToDo: trade player-planet
        qDebug() << "Player trade";
    }
}

void MainWindow::travelToStarSystem(unsigned starSystemId)
{

    qDebug() << "location before: " << player_->getLocation()->getCoordinates().x << "," << player_->getLocation()->getCoordinates().y;
    qDebug() << "health before: " << player_->getEngine()->getHealth();
    qDebug() << "can start before: " << player_->getEngine()->canStart();

    if(map_ != nullptr)
    {
        gameTimer_->stop();
        map_->hide();
        if(player_->getLocation()->getId() == starSystemId)
        {
            gameTimer_->start();
            return;
        }
    }

    //Remove everything from scene
    drawManager_->clearScene();

    //Set player's new location
    player_->setLocation(galaxy_->getStarSystemById(starSystemId));

    qDebug() << "location after: " << player_->getLocation()->getCoordinates().x << "," << player_->getLocation()->getCoordinates().y;
    qDebug() << "health after: " << player_->getEngine()->getHealth();
    qDebug() << "can start after: " << player_->getEngine()->canStart();

    auto starSystem = galaxy_->getStarSystemById(starSystemId);
    if(starSystem == nullptr) {
        throw Common::ObjectNotFoundException("Star system does not exist in the galaxy.");
        return;
    }

    for(auto ship : galaxy_->getShipsInStarSystem(starSystem->getName())){
        drawManager_->drawShip(ship);
    }

    qDebug() << drawManager_->getNumberOfShips();
    ui->lbSSEnemies->setText(QString::number(drawManager_->getNumberOfShips()));

    const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None" };
    ui->lbSSName->setText(starSystem->getName().data());
    ui->lbSSEconomy->setText(economy[starSystem->getEconomy()]);
    ui->lbSSPopulation->setText(QString::number(starSystem->getPopulation()));
    ui->lbSSCoordinates->setText("x: " + QString::number(starSystem->getCoordinates().x*5000) +
                                 " y: " + QString::number(starSystem->getCoordinates().y*5000));
    if(map_ != nullptr)
    {
        gameTimer_->start();
    }
}

void MainWindow::refreshUI()
{
    ui->graphicsView->centerOn(drawManager_->getPlayerShipUiByObject(player_));
    drawManager_->setFocusOnPlayer(player_);
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

//            NOTE: see planet.hh about notes about values below:
//            const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony" };
//            ui->lbSPEconomy->setText(economy[starPlanet->getEconomy()]);
//            ui->lbSPPopulation->setText(QString::number(starPlanet->getPopulation()));
//            ui->lbSPCoordinates->setText("x: " + QString::number(starPlanet->getCoordinates().x) +
//                                         " y: " + QString::number(starPlanet->getCoordinates().y));

            return;
        }
    }

    isPlayerTrading_ = false;
    ui->lbSPName->clear();
    ui->lbSPEconomy->clear();
    ui->lbSPPopulation->clear();
    ui->lbSPCoordinates->clear();
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
                 "<br/>You can not shoot during trading."
                 "<br/> Hope you like it."));
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
        connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)), this, SLOT(travelToStarSystem(unsigned)));
        map_ = new MapWindow(userActionHandler_, galaxy_->getStarSystemVector(), this);
        map_->setModal(true);
        map_->exec();
    }
    else
    {
        map_->show();
    }
}

