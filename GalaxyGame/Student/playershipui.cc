#include "playershipui.hh"
#include "utility.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>
#include <QTimer>

#define PLAYERSPEED_MOVEMENT 0.3

PlayerShipUi::PlayerShipUi(QPixmap pixmap, int posX, int posY, QObject *parent):
    QObject(parent)
{
    setPixmap(pixmap);
//    setScale(0.1);
    setTransformOriginPoint((boundingRect().center().x()),(boundingRect().center().y()));

    setPos(posX, posY);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setZValue(1);

    // ToDo: Threads
    keyMovement = new QTimer(this);
    connect(keyMovement, SIGNAL(timeout()), this, SLOT(updateMovement()));
    keyMovement->start(50);
}



void PlayerShipUi::keyPressEvent(QKeyEvent *event)
{    
    qDebug() << pos().x() << pos().y();
    if(!event->isAutoRepeat())
    {
        pressedKeys.insert(event->key());
        updateMovement();
    }
}

void PlayerShipUi::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        pressedKeys.remove(event->key());
    }
}

void PlayerShipUi::goLeft()
{
    setRotation(rotation()-5);
}

void PlayerShipUi::goRight()
{
    setRotation(rotation()+5);
}

void PlayerShipUi::goUp(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    setPos(x()+diffX, y()+diffY);
}

void PlayerShipUi::goDown(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    setPos(x()-diffX, y()-diffY);
}

void PlayerShipUi::updateMovement()
{
    for(int key : pressedKeys)
    {
        moveAccordingToPressedKey(key);
    }
}

void PlayerShipUi::moveAccordingToPressedKey(int key)
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
