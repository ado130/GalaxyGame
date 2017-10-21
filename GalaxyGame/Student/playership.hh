#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

#include <memory>
#include "galaxy.hh"
#include "ship.hh"

// ToDo: inherit this class from Common::Ship
class PlayerShip : public QGraphicsPixmapItem
{
public:
    PlayerShip(std::shared_ptr<Student::Galaxy> galaxy, QGraphicsScene *scene);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    std::shared_ptr<Student::Galaxy> galaxy_;
    QGraphicsScene *scene_;
};

#endif // PLAYERSHIP_H
