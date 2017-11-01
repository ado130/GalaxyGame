#include "playership.hh"
#include "bullet.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>
#include <QTimer>

#define PLAYERSPEED_MOVEMENT 0.5

// ToDo: "Cleaning the code" - logic here, move QT-related stuff to new class
PlayerShip::PlayerShip(QObject *parent, std::shared_ptr<Common::ShipEngine> engine,
                       std::shared_ptr<Common::StarSystem> initialLocation,
                       std::shared_ptr<Common::IEventHandler> events):
    QObject(parent),
    Ship(engine, initialLocation, events),
    QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/images/playerShip.png"));
    setScale(0.1);
    setTransformOriginPoint((boundingRect().center().x()),(boundingRect().center().y()));
    setPos(800/2, 600/2);

    // ToDo: Threads
    keyMovement = new QTimer(this);
    connect(keyMovement, SIGNAL(timeout()), this, SLOT(updateMovement()));
    keyMovement->start(50);

    // ToDo: Settings for MAX_LOAN_ALLOWANCE
    statistics = Student::Statistics(5000);
}

bool PlayerShip::decideAction()
{
    return 0;
}

Student::Statistics PlayerShip::getStatistics()
{
    return statistics;
}

void PlayerShip::keyPressEvent(QKeyEvent *event)
{    
    if(!event->isAutoRepeat())
    {
        pressedKeys.insert(event->key());
        updateMovement();
    }
}

void PlayerShip::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        pressedKeys.remove(event->key());
    }
}

void PlayerShip::goLeft()
{
    setRotation(rotation()-5);
}

void PlayerShip::goRight()
{
    setRotation(rotation()+5);
}

void PlayerShip::goUp(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    setPos(x()+diffX, y()+diffY);
}

void PlayerShip::goDown(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    setPos(x()-diffX, y()-diffY);
}

void PlayerShip::updateMovement()
{
    for(int key : pressedKeys)
    {
        //qDebug() << key << endl;
        moveAccordingToPressedKey(key);
    }
}

void PlayerShip::moveAccordingToPressedKey(int key)
{
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;
    if(key == Qt::Key_Left)
    {
        //The ship goes back -> we want to rotate back of the ship
        //to the left -> front goes to the right
        if(pressedKeys.contains(Qt::Key_Down))
        {
            goRight();
        }
        else
        {
            goLeft();
        }
    }
    else if(key == Qt::Key_Right)
    {
        if(pressedKeys.contains(Qt::Key_Down))
        {
            goLeft();
        }
        else
        {
            goRight();
        }
    }
    else if(key == Qt::Key_Up)
    {
        goUp(width, height);
    }
    else if(key == Qt::Key_Down)
    {
        goDown(width, height);
    }
    else if(key == Qt::Key_Space)
    {
        emit pressedSpace();
    }
}
