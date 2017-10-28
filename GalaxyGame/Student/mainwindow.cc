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

#include <QDebug>
#include <QTextEdit>
#include <QTimer>
#include <QBrush>
#include <QInputDialog>
#include <QSettings>
#include <QtConcurrent>
#include <QFuture>

#define SCENE_WIDTH 800
#define SCENE_HEIGHT 600

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

    // Create scene for the game
    scene_ = new QGraphicsScene(this);

    QObject* galaxyObj = galaxy.get();
    connect(galaxyObj, SIGNAL(newShip(std::shared_ptr<Common::Ship>)),
            this, SLOT(createShip(std::shared_ptr<Common::Ship>)));
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete collisionTimer_;
    delete refreshTimer_;
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
    gameRunner_->spawnShips(128);

    // Add star systems to the galaxy
    createStarSystem();

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

    // ToDo: maybe execute this function to another thread
    collisionTimer_ = new QTimer();
    connect(collisionTimer_, &QTimer::timeout, this, &MainWindow::checkCollision);
    //collisionTimer_->start(20);
}

void MainWindow::createPlayer()
{
    std::shared_ptr<Common::ShipEngine> shipEngine = std::make_shared<Common::WormHoleDrive>(galaxy_);
    std::shared_ptr<Common::StarSystem> initialLocation = std::make_shared<Common::StarSystem>("Earth", Common::StarSystem::Colony, 0, 10000, Common::Point(0, 0));
    player_ = new PlayerShip(this, shipEngine, initialLocation, handler_);
    connect(player_, &PlayerShip::fireBullet, this, &MainWindow::fireBullet);
}

void MainWindow::fireBullet()
{
    qreal width = player_->scale()*player_->boundingRect().size().width()/2;
    qreal height = player_->scale()*player_->boundingRect().size().height()/2;

    Bullet *bullet = new Bullet();
    bullet->setRotation(player_->rotation());
    bullet->setPos(player_->x() + width * cos( (player_->rotation()-90) * M_PI / 180.0 ),
                   player_->y() + height * sin( (player_->rotation()-90) * M_PI / 180.0 ));
    scene_->addItem(bullet);
}

void MainWindow::createStarSystem()
{
    auto starSystem = galaxy_->getStarSystemVector();
    for(auto k : starSystem)
    {
        StarPlanet *starPlanet = new StarPlanet(k->getName(), k->getEconomy(),k->getId(), k->getPopulation(), k->getCoordinates());
        scene_->addItem(starPlanet);
    }
}

void MainWindow::createShip(std::shared_ptr<Common::Ship> ship)
{
    NPCShip *npcship = new NPCShip(ship.get()->getEngine(), ship.get()->getLocation(), handler_);
    scene_->addItem(npcship);
}

void MainWindow::refreshUI()
{
    ui->graphicsView->centerOn(player_);

    QString playerCoor = QString(tr("Player coordinates: %1 %2")).arg(QString::number(player_->x(), 'f', 1)).arg(QString::number(player_->y(), 'f', 1));
    ui->lbPlayerCoor->setText(playerCoor);
}

void MainWindow::checkCollision()
{
    for(auto k : scene_->items())
    {
        QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(k);
        if(typeid (*k) == typeid (Bullet))
        {
            for(int i = 0, n = colliding_Items.size(); i<n; ++i)
            {
                if(typeid (*(colliding_Items[i])) == typeid (NPCShip))
                {
                    scene_->removeItem(colliding_Items[i]);
                    scene_->removeItem(k);

                    delete colliding_Items[i];
                    //delete k;
                }
            }
        }
        else if(typeid (*k) == typeid (PlayerShip))
        {
            for(int i = 0, n = colliding_Items.size(); i<n; ++i)
            {
                if(typeid (*(colliding_Items[i])) == typeid (StarPlanet))
                {
                    // player is on the planet
                }
            }
        }
    }
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
