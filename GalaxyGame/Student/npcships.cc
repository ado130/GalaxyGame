#include "npcships.hh"

#include <QTimer>

#define PI 3.14159265

NPCShips::NPCShips()
{  
    setPixmap(QPixmap(":/images/images/NPCShip.png"));

    setScale(0.2);

    int positionX = rand() % 700;
    int positionY = rand() % 500;
    setPos(positionX, positionY);

    QTimer * timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &NPCShips::move);
    timer->start(250);
}

void NPCShips::move()
{
    int randomMove = rand() % 4;
    int randomRotation = rand() % 361 - 180;
    if(randomMove == 0)
    {
        setTransformOriginPoint(QPoint(18,7));
        setRotation(rotation()-randomRotation);
    }
    else if(randomMove == 1)
    {
        setTransformOriginPoint(QPoint(18,7));
        setRotation(rotation()+randomRotation);
    }
    else if(randomMove == 2)
    {   // ToDo: movement is not correct
        qreal diffX = 0, diffY = 0;
       // diffX = rect().width()-rect().x();
        //diffY = rect().height()-rect().y();
        diffX *= cos( rotation() * PI / 180.0 );
        diffY *= sin( rotation() * PI / 180.0 );
        setPos(x() + diffX, y() + diffY);
    }
    else if(randomMove == 3)
    {   // ToDo: movement is not correct
        qreal diffX = 0, diffY = 0;
       // diffX = rect().width()-rect().x();
       // diffY = rect().height()-rect().y();
        diffX *= cos( rotation() * PI / 180.0 );
        diffY *= sin( rotation() * PI / 180.0 );
        setPos(x() - diffX, y() - diffY);
    }
}
