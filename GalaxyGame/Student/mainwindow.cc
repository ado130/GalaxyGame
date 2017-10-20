#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "eventhandler.hh"

#include "playership.hh"

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<Student::Galaxy> galaxy, std::shared_ptr<Common::IGameRunner> gameRunner) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    galaxy_ = galaxy;
    gameRunner_ = gameRunner;

    // Create scene for the game
    scene_ = new QGraphicsScene;

    // Add player to the galaxy
    PlayerShip *player = new PlayerShip(galaxy_);
    player->setRect(0, 0, 100, 100);
    scene_->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    // Add scene to the view
    ui->graphicsView->setScene(scene_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
