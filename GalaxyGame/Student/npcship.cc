#include "npcship.hh"

#include <QTimer>

NPCShip::NPCShip()
{  
    setPixmap(QPixmap(":/images/images/NPCShip.png"));

    setScale(0.2);

    int positionX = rand() % 800;
    int positionY = rand() % 600;
    setPos(positionX, positionY);

    QTimer * timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &NPCShip::move);
    timer->start(250);
}

void NPCShip::move()
{
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;

    int randomMove = rand() % 2 + 2;
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
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 );
        setPos(x() + diffX, y() + diffY);
    }
    else if(randomMove == 3)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 );
        setPos(x() - diffX, y() - diffY);
    }
}
