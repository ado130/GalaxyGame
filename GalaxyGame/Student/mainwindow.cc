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
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete refreshTimer_;
    delete gameTimer_;
    delete collisionTimer_;
    delete player_;
    delete ui;
}

void MainWindow::startGame()
{
    // ToDo: do not ignore ToDo's
    //bool ok;
    //QString nickName = QInputDialog::getText(this, tr("Enter nickname"),
    //                                      tr("Nickname:"), QLineEdit::Normal,
    //                                      "", &ok);

    scene_->clear();

    qDebug() << "New game";
    // Backgroudn for scene
    scene_->setBackgroundBrush( Qt::lightGray );

    // Add player to the galaxy
    createPlayer();
    scene_->addItem(player_);
    player_->setFlag(QGraphicsItem::ItemIsFocusable);
    player_->setFocus();
    player_->setZValue(1);

    // Add enemies to the galaxy
    gameRunner_->spawnShips(50);

    // Generate environment for initialposition of player (initial starSystem)
    createPlanetsForStarSystem(player_->getLocation().get()->getId());

    // Add scene to the view
    ui->graphicsView->setScene(scene_);
    ui->graphicsView->scene()->setFocusItem(player_);

    // Base coordinates == player start position, there will be player's base
    QString baseCoor = QString(tr("Base coordinates: %1 %2")).arg(QString::number(player_->x(), 'f', 1)).arg(QString::number(player_->y(), 'f', 1));
    ui->lbBaseCoor->setText(baseCoor);

    // Set timers
    refreshTimer_ = new QTimer();
    connect(refreshTimer_, &QTimer::timeout, this, &MainWindow::refreshUI);
    refreshTimer_->start(1);

    // ToDo: solve the crash problem
    collisionTimer_ = new QTimer();
    connect(collisionTimer_, &QTimer::timeout, this, &MainWindow::executeCollisionCheck);
    connect(this, SIGNAL(startCollisionTimer()), collisionTimer_, SLOT(start()));
    connect(this, &MainWindow::stopCollisionTimer, collisionTimer_, &QTimer::stop);
    //collisionTimer_->start(2000);

    gameTimer_ = new QTimer();
    connect(gameTimer_, &QTimer::timeout, this, &MainWindow::gameEvent);
    gameTimer_->start(50);
}

void MainWindow::createPlayer()
{
    std::shared_ptr<Common::ShipEngine> shipEngine = std::make_shared<Common::WormHoleDrive>(galaxy_);
    std::shared_ptr<Common::StarSystem> initialLocation = std::make_shared<Common::StarSystem>("Earth", Common::StarSystem::Colony, 0, 10000, Common::Point(0, 0));
    player_ = new PlayerShip(this, shipEngine, initialLocation, handler_);
    connect(player_, &PlayerShip::pressedSpace, this, &MainWindow::pressedSpace);
}

void MainWindow::pressedSpace()
{
    if(isPlayerTrading_)
    {
        // ToDo: trade player-planet
        qDebug() << "Player trade";
    }
    else
    {
        qreal width = player_->scale()*player_->boundingRect().size().width()/2;
        qreal height = player_->scale()*player_->boundingRect().size().height()/2;

        Bullet *bullet = new Bullet();
        bullet->setRotation(player_->rotation());
        // ToDo: bullet position
        bullet->setPos(player_->x() - width * cos( (player_->rotation()-90) * M_PI / 180.0 ),
                       player_->y() - height * sin( (player_->rotation()-90) * M_PI / 180.0 ));
        scene_->addItem(bullet);
    }
}

void MainWindow::createPlanetsForStarSystem(unsigned starSystemId)
{
    // ToDo: if player in SS for the first time -> generate planets
    //       Store planets somewhere so they are the same for certain SS everyTime

    // ToDo: Create random positions of planets
    auto starSystem = galaxy_->getStarSystemVector();
    for(Common::StarSystem::StarSystemVector::size_type i = 0; i<starSystem.size(); ++i)
    {
        StarPlanet *starPlanet = new StarPlanet(starSystem.at(i).get()->getCoordinates());
        scene_->addItem(starPlanet);
        starPlanetList_.append(qMakePair(starSystem.at(i), starPlanet));
    }
//    ui->lbCntStarSystems->setText(QString::number(starSystemList_.count()));
}

void MainWindow::shipEvent(std::shared_ptr<Common::Ship> ship, bool newShip)
{
    if(newShip)
    {
        NPCShip *npcship = new NPCShip();
        scene_->addItem(npcship);
        shipList_.append(qMakePair(ship, npcship));
    }
    else
    {
        QGraphicsItem *item = getSceneShip(ship);
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
    // ToDo: implement repaint() of starsystems and move with playership
    map->hide();
    qDebug() << "Mainwindow - playerShip make move to starSystem " << starSystemId;
}

void MainWindow::shipMovement(std::shared_ptr<Common::Ship> ship, int diffX, int diffY)
{
    QGraphicsItem *item = getSceneShip(ship);
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

QGraphicsItem* MainWindow::getSceneStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    for(auto k : starPlanetList_)
    {
        if(k.first == starSystem)
        {
            return k.second;
        }
    }

    return nullptr;
}

std::shared_ptr<Common::StarSystem> MainWindow::getStarSystemByItem(QGraphicsItem* item)
{
    for(auto k : starPlanetList_)
    {
        if(k.second == item)
        {
            return k.first;
        }
    }

    return nullptr;
}

void MainWindow::refreshUI()
{
    ui->graphicsView->centerOn(player_);

    QString playerCoor = QString(tr("Player coordinates: %1 %2")).arg(QString::number(player_->x(), 'f', 1)).arg(QString::number(player_->y(), 'f', 1));
    ui->lbPlayerCoor->setText(playerCoor);
}

void MainWindow::gameEvent()
{
    gameRunner_->createActions();
    gameRunner_->doActions();
}

void MainWindow::executeCollisionCheck()
{
    QFuture<void> collision = QtConcurrent::run(this, &MainWindow::checkCollision);
}

void MainWindow::checkCollision()
{
    //emit stopCollisionTimer();
    for(auto k : scene_->items())
    {
        QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(k);
        if(typeid (*k) == typeid (Bullet))
        {
            for(int i = 0, n = colliding_Items.size(); i<n; ++i)
            {
                if(typeid (*(colliding_Items[i])) == typeid (NPCShip))
                {
                    qDebug() << "Bullet-NPC collision";
                    scene_->removeItem(colliding_Items[i]);
                    scene_->removeItem(k);

                    delete colliding_Items[i];
                    //delete k;
                }
            }
        }
        else if(typeid (*k) == typeid (PlayerShip))
        {
            QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(k);
            for(int i = 0, n = colliding_Items.size(); i<n; ++i)
            {
                if(typeid (*(colliding_Items[i])) == typeid (StarPlanet))
                {
                    isPlayerTrading_ = true;
                    const char * economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony" };
                    auto starSystem = getStarSystemByItem(colliding_Items[i]);
                    ui->lbName->setText(starSystem->getName().data());
                    ui->lbEconomy->setText(economy[starSystem->getEconomy()]);
                    ui->lbPopulation->setText(QString::number(starSystem->getPopulation()));
                    ui->lbCoordinates->setText("x: " + QString::number(starSystem->getCoordinates().x) +
                                               "y: " + QString::number(starSystem->getCoordinates().y));
                }
                else
                {
                    isPlayerTrading_ = false;
                    ui->lbName->clear();
                    ui->lbEconomy->clear();
                    ui->lbPopulation->clear();
                    ui->lbCoordinates->clear();
                }
            }
        }
    }
    //emit startCollisionTimer();
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
    help->setWindowFlag(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->append(tr("<h1>About</h1>Welcome to Semicolon Spaceship game."
                 "<br/>Lucia Kuchárová & Andrej Vlasatý"
                 "<br/> Hope you like it."));
    help->show();
}

void MainWindow::on_actionHelp_triggered()
{
    QTextEdit* help = new QTextEdit();
    help->setWindowFlag(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->append(tr("<h1>Help</h1>Use arrow keys to move."
                 "<br/>Fly over the planet and press space to trade with the planet."
                 "<br/>You can not shoot during trading."
                 "<br/> Hope you like it."));
    help->show();
}

void MainWindow::loadSettings()
{

}

void MainWindow::saveSettings()
{

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
    if(map == nullptr)
    {
        QObject* eventHandlerObj = dynamic_cast<QObject*>(userActionHandler_.get());
        connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)), this, SLOT(travelToStarSystem(unsigned)));
        map = new MapWindow(userActionHandler_, galaxy_->getStarSystemVector(), this);
        map->setModal(true);
        map->exec();
    }
    else
    {
        map->show();
    }
}

