#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include <memory>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "ship.hh"

// ToDo: inherit this class from Common::Ship
class NPCShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    NPCShip();

private:

private slots:
    void move();
};

#endif // NPCSHIP_HH
