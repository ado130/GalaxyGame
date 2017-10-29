#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "ship.hh"

class NPCShip : public Common::Ship, public QGraphicsPixmapItem
{

public:
    NPCShip(std::shared_ptr<Common::Ship> ship,
            std::shared_ptr<Common::IEventHandler> events);

    bool decideAction();

private:

    bool decideToMove();
private slots:
    void move();
};

#endif // NPCSHIP_HH
