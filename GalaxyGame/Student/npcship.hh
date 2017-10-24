#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "ship.hh"

// ToDo: inherit this class from Common::Ship
class NPCShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    NPCShip(QGraphicsScene *scene);

private:
    QGraphicsScene *scene_;

private slots:
    void move();
};

#endif // NPCSHIP_HH
