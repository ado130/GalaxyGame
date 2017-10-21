#ifndef NPCSHIPS_HH
#define NPCSHIPS_HH

#include <memory>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "ship.hh"

// ToDo: inherit this class from Common::Ship
class NPCShips : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    NPCShips();

private:

private slots:
    void move();
};

#endif // NPCSHIPS_HH
