#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <memory>

#include "galaxy.hh"
#include "ship.hh"

class PlayerShip : public Common::Ship, public QGraphicsPixmapItem
{
public:
    PlayerShip(std::shared_ptr<Student::Galaxy> galaxy, QGraphicsScene *scene,
               std::shared_ptr<Common::ShipEngine> engine,
               std::shared_ptr<Common::StarSystem> initialLocation,
               std::shared_ptr<Common::IEventHandler> events);

    bool decideAction();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    std::shared_ptr<Student::Galaxy> galaxy_;
    QGraphicsScene *scene_;
};

#endif // PLAYERSHIP_H
