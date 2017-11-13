#include "npcshipui.hh"

#include <QDebug>

#define NPCSHIPSPEED_MOVEMENT 0.1

NPCShipUi::NPCShipUi(QPixmap pixmap, int posX, int posY, QObject *parent):
    QObject(parent)
{  
    setPixmap(pixmap);
    setScale(0.2);
    setTransformOriginPoint((boundingRect().center().x()),(boundingRect().center().y()));

    setPos(posX, posY);

    keyMovement = new QTimer(this);
    connect(keyMovement, SIGNAL(timeout()), this, SLOT(moveForward()));
    keyMovement->start(50);

    randomKeyPress = new QTimer(this);
    connect(randomKeyPress, SIGNAL(timeout()), this, SLOT(randomChangeOfDirection()));
    randomKeyPress->start(Common::randomMinMax(1000, 100000));

    randomChangeOfDirection();

}

void NPCShipUi::randomChangeOfDirection()
{
    int randomKey = Common::randomMinMax(0,2);
    if(randomKey == 1){
        goLeft();
    }
    else if (randomKey == 2){
        goRight();
    }
    else{
        //direction doesn't change
    }
}

void NPCShipUi::goLeft()
{
    setRotation(rotation()-Common::randomMinMax(1, 180));
}

void NPCShipUi::goRight()
{
    setRotation(rotation()+Common::randomMinMax(1, 180));
}

void NPCShipUi::goUp(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    setPos(x()+diffX, y()+diffY);
}

void NPCShipUi::goDown(qreal width, qreal height)
{
    qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 ) * NPCSHIPSPEED_MOVEMENT;
    setPos(x()-diffX, y()-diffY);
}

void NPCShipUi::moveForward()
{
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;
    goUp(width, height);
}
