#include "npcship.hh"
#include "moveaction.hh"

#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

NPCShip::NPCShip(std::shared_ptr<Common::Ship> ship,
                 std::shared_ptr<Common::IEventHandler> events):
    Ship(ship.get()->getEngine(), ship.get()->getLocation(), events),
    QGraphicsPixmapItem()
{  
    setPixmap(QPixmap(":/images/images/NPCShip.png"));
    setScale(0.2);
    setTransformOriginPoint(static_cast<int>(scale()*boundingRect().size().width()/2), static_cast<int>(scale()*boundingRect().size().height()/2));

    setName(ship.get()->getName());

    // ToDo: NPC position
    int position = Common::randomMinMax(-50, 50);
    setPos(ship.get()->getLocation()->getCoordinates().x*100 + position, ship.get()->getLocation()->getCoordinates().y*100 + position);
}

bool NPCShip::decideAction()
{
    if(isAbandoned())
    {
        return false;
    }

    if(currentAction_)
    {
        return false;
    }

    if(decideToMove())
    {
        return true;
    }

    return false;
}

bool NPCShip::decideToMove()
{
    if (!engine_)
    {
        return true;
    }

    auto systems = engine_->getValidDestinations(location_);

    if (systems.size() < 1)
    {
        return false;
    }

    int chosen_index = Common::randomMinMax(0, systems.size() - 1);
    auto chosen_location = systems.at(chosen_index);

    auto ma = std::make_shared<Common::MoveAction>(shared_from_this(), chosen_location, events_);

    if (ma->canDo())
    {
        currentAction_ = ma;
        return true;
    }

    return false;
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
