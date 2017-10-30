#include "playership.hh"
#include "bullet.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>

#define PLAYERSPEED_MOVEMENT 0.15

PlayerShip::PlayerShip(QObject *parent, std::shared_ptr<Common::ShipEngine> engine,
                       std::shared_ptr<Common::StarSystem> initialLocation,
                       std::shared_ptr<Common::IEventHandler> events):
    QObject(parent),
    Ship(engine, initialLocation, events),
    QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/images/playerShip.png"));
    setScale(0.1);
    setTransformOriginPoint(static_cast<int>(scale()*boundingRect().size().width()/2), static_cast<int>(scale()*boundingRect().size().height()/2));
    setPos(800/2, 600/2);

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
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;

    if(event->key() == Qt::Key_Left)
    {
        setRotation(rotation()-5);
    }
    else if(event->key() == Qt::Key_Right)
    {
        setRotation(rotation()+5);
    }
    else if(event->key() == Qt::Key_Up)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
        setPos(x() + diffX, y() + diffY);
        // ToDo: check calculations
    }
    else if(event->key() == Qt::Key_Down)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
        setPos(x() - diffX, y() - diffY);
    }
    else if(event->key() == Qt::Key_Space)
    {
        emit pressedSpace();
    }
}
