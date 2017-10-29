#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class NPCShip : public QGraphicsPixmapItem
{

public:
    NPCShip();

private slots:
    void move();
};

#endif // NPCSHIP_HH
