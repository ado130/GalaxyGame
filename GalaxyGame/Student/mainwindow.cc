#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "eventhandler.hh"
#include "playership.hh"
#include "npcships.hh"

#include <QDebug>
#include <QTextEdit>
#include <QTimer>

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
    scene_ = std::make_shared<QGraphicsScene>();

    //scene_->setSceneRect(0, 0, 800, 600);

    // Add player to the galaxy
    //std::shared_ptr<PlayerShip> player = std::make_shared<PlayerShip>(scene_, galaxy_);
    player = new PlayerShip(galaxy_, scene_);
    scene_->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Add enemies to the galaxy
    for(unsigned int i = 0; i<10; i++)
    {
        NPCShips * npcship = new NPCShips();
        scene_->addItem(npcship);
    }

    // Add scene to the view
    ui->graphicsView->setScene(scene_.get());

    // Base coordinates == player start position, there will be player's base
    QString baseCoor = QString("Base coordinates: %1 %2").arg(ui->graphicsView->width()/2).arg(ui->graphicsView->height()/2);
    ui->lbBaseCoor->setText(baseCoor);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::refreshUI);
    timer->start(100);
}

void MainWindow::refreshUI()
{
    QString playerCoor = QString("Player coordinates: %1 %2").arg(player->x()).arg(player->y());
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
