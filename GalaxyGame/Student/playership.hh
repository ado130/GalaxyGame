#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <memory>
#include "shipdesign.hh"
#include "galaxy.hh"
#include "ship.hh"

#include <QKeyEvent>

// ToDo: inherit this class from Common::Ship
class PlayerShip : public ShipDesign
{
public:
    PlayerShip(std::shared_ptr<Student::Galaxy> galaxy, std::shared_ptr<QGraphicsScene> scene);

    ~PlayerShip();

    void keyPressEvent(QKeyEvent *event);

private:
    std::shared_ptr<Student::Galaxy> galaxy_;
    std::shared_ptr<QGraphicsScene> scene_;
};

#endif // PLAYERSHIP_H
