#include "npcship.hh"

#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

NPCShip::NPCShip(std::shared_ptr<Common::ShipEngine> engine,
                 std::shared_ptr<Common::StarSystem> initialLocation,
                 std::shared_ptr<Common::IEventHandler> events):
    Ship(engine, initialLocation, events),
    QGraphicsPixmapItem()
{  
    setPixmap(QPixmap(":/images/images/NPCShip.png"));
    setScale(0.2);
    setTransformOriginPoint(static_cast<int>(scale()*boundingRect().size().width()/2), static_cast<int>(scale()*boundingRect().size().height()/2));

    setPos(initialLocation->getCoordinates().x*100, initialLocation->getCoordinates().y*100);
}

bool NPCShip::decideAction()
{
    return 0;
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
