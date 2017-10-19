#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <memory>
#include "galaxy.hh"
#include "ship.hh"

#include <QGraphicsRectItem>
#include <QKeyEvent>

class PlayerShip : public QGraphicsRectItem
{
public:
    PlayerShip(std::shared_ptr<Student::Galaxy> galaxy);

    void keyPressEvent(QKeyEvent *event);

private:
    std::shared_ptr<Student::Galaxy> galaxy_;
};

#endif // PLAYERSHIP_H
