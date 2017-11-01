#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "ship.hh"

class NPCShip : public QGraphicsPixmapItem
{

public:
    NPCShip(Common::Point point);

private slots:
    void move();
};

#endif // NPCSHIP_HH
