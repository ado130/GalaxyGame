#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "eventhandler.hh"
#include "playership.hh"
#include "npcship.hh"
#include "starplanet.hh"
#include "wormholedrive.hh"
#include "starsystem.hh"
#include "point.hh"
#include "bullet.hh"
#include "statisticswindow.hh"
#include "objectnotfoundexception.hh"

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

    // Create scene for the game
    scene_ = new QGraphicsScene(this);

    QObject* eventHandlerObj = dynamic_cast<QObject*>(handler.get());
    connect(eventHandlerObj, SIGNAL(shipEvent(std::shared_ptr<Common::Ship>, bool)),
            this, SLOT(shipEvent(std::shared_ptr<Common::Ship>, bool)));
    connect(eventHandlerObj, SIGNAL(shipMovement(std::shared_ptr<Common::Ship>, int, int)),
            this, SLOT(shipMovement(std::shared_ptr<Common::Ship>, int, int)));

    ui->pbShowMap->setEnabled(false);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete refreshTimer_;
    delete gameTimer_;
    delete collisionTimer_;
    delete player_;
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

    scene_->clear();

    qDebug() << "New game";
    // Background for scene
    scene_->setBackgroundBrush( Qt::lightGray );

    // Add player to the galaxy, must be called before travelToStarSystem
    createPlayer();

    // Generate environment for initialposition of player (initial starSystem)
    starPlanetList_.clear();
    createPlanetsForStarSystem();

    // Add enemies to the galaxy
    shipList_.clear();
    galaxy_->removeShips();
    gameRunner_->spawnShips(150);

    // Start location is player's location
    travelToStarSystem(player_->getLocation()->getId());

    // Add scene to the view
    ui->graphicsView->setScene(scene_);
    ui->graphicsView->scene()->setFocusItem(player_);

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

    ui->pbShowMap->setEnabled(true);
    ui->pbNewGame->setEnabled(true);
}

void MainWindow::createPlayer()
{
    std::shared_ptr<Common::ShipEngine> shipEngine = std::make_shared<Common::WormHoleDrive>(galaxy_);
    std::shared_ptr<Common::StarSystem> initialLocation = galaxy_->getRandomSystem();//std::make_shared<Common::StarSystem>("Earth", Common::StarSystem::Colony, 0, 10000, Common::Point(0, 0));
    player_ = new PlayerShip(this, shipEngine, initialLocation, handler_);
    player_->setFlag(QGraphicsItem::ItemIsFocusable);
    player_->setFocus();
    player_->setZValue(1);
    connect(player_, &PlayerShip::pressedSpace, this, &MainWindow::pressedSpace);
}

void MainWindow::pressedSpace()
{
    if(isPlayerTrading_)
    {
        // ToDo: trade player-planet
        qDebug() << "Player trade";
    }
}

void MainWindow::createPlanetsForStarSystem()
{
    unsigned int id = 0;
    auto starSystems = galaxy_->getStarSystemVector();
    for(auto k : starSystems)
    {
        for(unsigned int i = 0; i<5; ++i)      // e.g. 5 planets for each star system
        {
            StarPlanet *starPlanet = new StarPlanet(id++, k->getPopulation(), k->getCoordinates());      // ToDo: maybe change the popilation?
            starPlanetList_.insert(k->getId(), qMakePair(k, starPlanet));
        }
    }
    ui->lbCntStarSystems->setText(QString::number(starSystems.size()));
}

void MainWindow::shipEvent(std::shared_ptr<Common::Ship> ship, bool newShip)
{
    if(newShip)
    {
        NPCShip *npcship = new NPCShip(ship->getLocation()->getCoordinates());
        shipList_.append(qMakePair(ship, npcship));
    }
    else
    {
        QGraphicsItem *item = getSceneShip(ship);
        if(item == nullptr) return;
        scene_->removeItem(item);
        for(int i = 0; i<shipList_.size(); ++i)
        {
            if(shipList_.at(i).first == ship)
            {
                shipList_.removeAt(i);
                break;
            }
        }
    }

    ui->lbCntEnemies->setText(QString::number(shipList_.count()));
}

void MainWindow::travelToStarSystem(unsigned starSystemId)
{
    if(map_ != nullptr)
    {
        gameTimer_->stop();
        map_->hide();
        if(player_->getLocation()->getId() == starSystemId)
        {
            return;
        }
        scene_->removeItem(player_);
        scene_->clear();
    }

    scene_->addItem(player_);

    auto starSystem = galaxy_->getStarSystemById(starSystemId);
    if(starSystem == nullptr) throw Common::ObjectNotFoundException("Star system does not exist in the galaxy.");
    auto ships = galaxy_->getShipsInStarSystem(starSystem->getName());
    for(auto k : ships)
    {
        for(auto m : shipList_)
        {
            if(k == m.first)
            {
                scene_->addItem(m.second);
                break;
            }
        }
    }

    ui->lbSSEnemies->setText(QString::number(scene_->items().size()-1));

    for (auto k : starPlanetList_.values(starSystemId))
    {
        scene_->addItem(k.second);
    }

    const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None" };
    ui->lbSSName->setText(starSystem->getName().data());
    ui->lbSSEconomy->setText(economy[starSystem->getEconomy()]);
    ui->lbSSPopulation->setText(QString::number(starSystem->getPopulation()));
    ui->lbSSCoordinates->setText("x: " + QString::number(starSystem->getCoordinates().x*50) +
                                 " y: " + QString::number(starSystem->getCoordinates().y*50));

    player_->setFocus();
    if(map_ != nullptr)
    {
        gameTimer_->start();
    }
}

void MainWindow::shipMovement(std::shared_ptr<Common::Ship> ship, int diffX, int diffY)
{
    QGraphicsItem* item = getSceneShip(ship);
    if(item != nullptr)
    {
        item->setPos(item->x() + diffX, item->y() + diffY);
    }
}

QGraphicsItem* MainWindow::getSceneShip(std::shared_ptr<Common::Ship> ship)
{
    for(auto k : shipList_)
    {
        if(k.first == ship)
        {
            return k.second;
        }
    }

    return nullptr;
}

StarPlanet* MainWindow::getStarPlanetByItem(QGraphicsItem* item)
{
    for(auto k : starPlanetList_)
    {
        if(k.second == item)
        {
            return k.second;
        }
    }

    return nullptr;
}

void MainWindow::refreshUI()
{
    ui->graphicsView->centerOn(player_);
}

void MainWindow::gameEvent()
{
    gameRunner_->createActions();
    gameRunner_->doActions();
}

void MainWindow::checkCollision()
{
    QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(player_);
    for(int i = 0, n = colliding_Items.size(); i<n; ++i)
    {
        if(typeid (*(colliding_Items[i])) == typeid (NPCShip))
        {
            // ToDo: collision with NPC ship
            return;
        }
        else if(typeid (*(colliding_Items[i])) == typeid (StarPlanet))
        {
            isPlayerTrading_ = true;
            const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony" };
            const char* goods[] = { "Oil", "Natural gas", "Wood", "Diamonds", "Coal", "None" };
            auto starPlanet = getStarPlanetByItem(colliding_Items[i]);
            ui->lbSPName->setText(starPlanet->getName().data());
            ui->lbSPEconomy->setText(economy[starPlanet->getEconomy()]);
            ui->lbSPPopulation->setText(QString::number(starPlanet->getPopulation()));
            ui->lbSPCoordinates->setText("x: " + QString::number(starPlanet->getCoordinates().x) +
                                         " y: " + QString::number(starPlanet->getCoordinates().y));
            ui->lbSPGoods->setText(goods[starPlanet->getGoods()]);

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

