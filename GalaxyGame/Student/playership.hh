#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

#include "ship.hh"

class PlayerShip : public QObject, public Common::Ship, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    PlayerShip(QObject* parent = 0,
               std::shared_ptr<Common::ShipEngine> engine = 0,
               std::shared_ptr<Common::StarSystem> initialLocation = 0,
               std::shared_ptr<Common::IEventHandler> events = 0);

    bool decideAction();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void fireBullet();

};

#endif // PLAYERSHIP_H
