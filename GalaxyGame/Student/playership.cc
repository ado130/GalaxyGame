#include "playership.hh"

#include <QDebug>

PlayerShip::PlayerShip(std::shared_ptr<Student::Galaxy> galaxy)
{
    galaxy_ = galaxy;
}

void PlayerShip::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        qDebug() << "Left";
        // move left
    }
    else if(event->key() == Qt::Key_Right)
    {
        qDebug() << "Right";
        // move right
    }
    else if(event->key() == Qt::Key_Up)
    {
        qDebug() << "Up";
        // move up
    }
    else if(event->key() == Qt::Key_Down)
    {
        qDebug() << "Down";
        // move down
    }
    else if(event->key() == Qt::Key_Space)
    {
        qDebug() << "Space";
        // shoot
    }

}
