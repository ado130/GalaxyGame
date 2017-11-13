#include "playershipui.hh"
#include "utility.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>
#include <QTimer>

#define PLAYERSPEED_MOVEMENT 0.3

PlayerShipUi::PlayerShipUi(QPixmap pixmap, int posX, int posY, std::shared_ptr<Student::UserActionHandler> userActionHandler, QObject *parent):
    QObject(parent), handler_(userActionHandler)
{
    setPixmap(pixmap);
    setTransformOriginPoint((boundingRect().center().x()),(boundingRect().center().y()));

    setPos(posX, posY);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setZValue(1);

    keyMovement_ = new QTimer(this);
    connect(keyMovement_, SIGNAL(timeout()), this, SLOT(updateMovement()));
    keyMovement_->start(50);
}

void PlayerShipUi::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        pressedKeys_.insert(event->key());
        updateMovement();
    }
}

void PlayerShipUi::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        pressedKeys_.remove(event->key());
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
    handler_->pressedPlayerMovementKey(this, x()+diffX, y()+diffY);
}

void PlayerShipUi::goDown(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * PLAYERSPEED_MOVEMENT;
    handler_->pressedPlayerMovementKey(this, x()-diffX, y()-diffY);
}

void PlayerShipUi::updateMovement()
{
    if(pressedKeys_.count() > 0)
    {
        foreach(const int &value, pressedKeys_)
        {
            moveAccordingToPressedKey(value);
        }
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
        if(pressedKeys_.contains(Qt::Key_Down))
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
        if(pressedKeys_.contains(Qt::Key_Down))
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
        keyMovement_->stop();
        handler_->pressedSpace();
        pressedKeys_.remove(Qt::Key_Space);
        keyMovement_->start();
    }
}
