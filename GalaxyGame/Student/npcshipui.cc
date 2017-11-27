#include "npcshipui.hh"

#include <QDebug>
#include <cassert>

#define NPCSHIPSPEED_MOVEMENT 0.1

Ui::NPCShipUi::NPCShipUi(QPixmap pixmap, int posX, int posY, QObject *parent):
    QObject(parent)
{  
    setPixmap(pixmap);
    setScale(0.2);
    setTransformOriginPoint((boundingRect().center().x()),(boundingRect().center().y()));
    setZValue(-1);

    setPos(posX, posY);
    canMove_ = true;

    keyMovement_ = new QTimer(this);
    connect(keyMovement_, SIGNAL(timeout()), this, SLOT(moveForward()));
    keyMovement_->start(50);

    randomKeyPress_ = new QTimer(this);
    connect(randomKeyPress_, SIGNAL(timeout()), this, SLOT(randomChangeOfDirection()));
    randomKeyPress_->start(Common::randomMinMax(1000, 100000));

    randomChangeOfDirection();

}

void Ui::NPCShipUi::changePixmapAndRotation(QPixmap pixmap, int rotation)
{
    setPixmap(pixmap);
    setRotation(rotation);
}

void Ui::NPCShipUi::canMove(bool canMove)
{
    assert(keyMovement_);
    assert(randomKeyPress_);

    if(canMove_ && !canMove)
    {
        keyMovement_->stop();
        randomKeyPress_->stop();
    }
    else if(!canMove_ && canMove)
    {
        keyMovement_->start();
        randomKeyPress_->start();
    }
    canMove_ = canMove;
}

bool Ui::NPCShipUi::canMove()
{
    return canMove_;
}

void Ui::NPCShipUi::randomChangeOfDirection()
{
    int randomKey = Common::randomMinMax(0,2);
    if(randomKey == 1)
    {
        goLeft();
    }
    else if (randomKey == 2)
    {
        goRight();
    }
    else{
        //direction doesn't change
    }
}

void Ui::NPCShipUi::goLeft()
{
    setRotation(rotation()-Common::randomMinMax(1, 180));
}

void Ui::NPCShipUi::goRight()
{
    setRotation(rotation()+Common::randomMinMax(1, 180));
}

void Ui::NPCShipUi::goUp(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    setPos(x()+diffX, y()+diffY);
}

void Ui::NPCShipUi::goDown(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    setPos(x()-diffX, y()-diffY);
}

void Ui::NPCShipUi::moveForward()
{
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;
    goUp(width, height);
}
