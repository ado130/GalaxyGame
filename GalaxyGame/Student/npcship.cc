#include "npcship.hh"

#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>

NPCShip::NPCShip(QGraphicsScene *scene)
{  
    scene_ = scene;

    setPixmap(QPixmap(":/images/images/NPCShip.png"));
    setScale(0.2);
    setTransformOriginPoint(static_cast<int>(scale()*boundingRect().size().width()/2), static_cast<int>(scale()*boundingRect().size().height()/2));

    bool bCollision = false;
    do
    {
        int positionX = rand() % 700;
        int positionY = rand() % 500;
        setPos(positionX, positionY);
        QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(this);
        for(int i = 0, n = colliding_Items.size(); i<n; ++i)
        {
            if(typeid (*(colliding_Items[i])) == typeid (NPCShip))
            {
                qDebug() << "NPC - collision";
                bCollision = true;
            }
            else
            {
                bCollision = false;
            }
        }
    }while(bCollision);

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
        setRotation(rotation()-randomRotation);
    }
    else if(randomMove == 1)
    {
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
