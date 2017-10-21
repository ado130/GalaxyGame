#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "eventhandler.hh"
#include "playership.hh"
#include "npcship.hh"
#include "starplanet.hh"

#include <QDebug>
#include <QTextEdit>
#include <QTimer>
#include <QBrush>

#define SCENE_WIDTH 800
#define SCENE_HEIGHT 600

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<Common::IEventHandler> handler, std::shared_ptr<Student::Galaxy> galaxy, std::shared_ptr<Common::IGameRunner> gameRunner) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    handler_ = handler;
    galaxy_ = galaxy;
    gameRunner_ = gameRunner;
}

MainWindow::~MainWindow()
{
    delete timer;
    delete player;
    delete ui;
}

void MainWindow::startGame()
{
    // ToDo: do not ignore ToDo's

    qDebug() << "New game";
    // Create scene for the game
    scene_ = new QGraphicsScene(this);

    //scene_->setSceneRect(SCENE_WIDTH/2 - ui->graphicsView->width()/2, SCENE_WIDTH/2 - ui->graphicsView->height()/2, SCENE_WIDTH/2, SCENE_HEIGHT/2);

    // Backgroudn for scene
    scene_->setBackgroundBrush( Qt::lightGray );

    // Add player to the galaxy
    player = new PlayerShip(galaxy_, scene_);
    scene_->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Add enemies to the galaxy
    for(unsigned int i = 0; i<5; i++)
    {
        NPCShip *npcship = new NPCShip();
        scene_->addItem(npcship);
    }

    // Add star system to the galaxy
    for(unsigned int i = 0; i<3; i++)
    {
        StarPlanet *starPlanet = new StarPlanet();
        scene_->addItem(starPlanet);
    }

    // Add scene to the view
    ui->graphicsView->setScene(scene_);

    // Base coordinates == player start position, there will be player's base
    QString baseCoor = QString("Base coordinates: %1 %2").arg(QString::number(player->x(), 'f', 1)).arg(QString::number(player->y(), 'f', 1));
    ui->lbBaseCoor->setText(baseCoor);

    // Set timer to refresh UI information
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::refreshUI);
    timer->start(100);
}

void MainWindow::refreshUI()
{
    QString playerCoor = QString("Player coordinates: %1 %2").arg(QString::number(player->x(), 'f', 1)).arg(QString::number(player->y(), 'f', 1));
    ui->lbPlayerCoor->setText(playerCoor);
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
    help->append("<h1>About</h1>Welcome to Semicolon Spaceship game.<br/> Hope you like it.");
    help->show();
}

void MainWindow::on_actionHelp_triggered()
{
    QTextEdit* help = new QTextEdit();
    help->setWindowFlag(Qt::Window); //or Qt::Tool, Qt::Dialog if you like
    help->setReadOnly(true);
    help->append("<h1>Help</h1>Welcome to my help.<br/> Hope you like it.");
    help->show();
}
