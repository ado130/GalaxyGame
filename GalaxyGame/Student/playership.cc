#include "playership.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>

#define PI 3.14159265


PlayerShip::PlayerShip(std::shared_ptr<Student::Galaxy> galaxy, std::shared_ptr<QGraphicsScene> scene)
{
    galaxy_ = galaxy;
    scene_ = scene;

    setPos(800/2, 600/2);
}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        setTransformOriginPoint(QPoint(18,7));
        setRotation(rotation()-5);
    }
    else if(event->key() == Qt::Key_Right)
    {
        setTransformOriginPoint(QPoint(18,7));
        setRotation(rotation()+5);
    }
    else if(event->key() == Qt::Key_Up)
    {   // ToDo: movement is not correct
        qreal diffX = 0, diffY = 0;
        diffX = rect().width()-rect().x();
        diffY = rect().height()-rect().y();
        diffX *= cos( rotation() * PI / 180.0 );
        diffY *= sin( rotation() * PI / 180.0 );
        setPos(x() + diffX, y() + diffY);
        // ToDo: check calculations
        scene_->setSceneRect(scene_->sceneRect().x()+diffX, scene_->sceneRect().y()+diffY, scene_->sceneRect().width(), scene_->sceneRect().height());
    }
    else if(event->key() == Qt::Key_Down)
    {   // ToDo: movement is not correct
        qreal diffX = 0, diffY = 0;
        diffX = rect().width()-rect().x();
        diffY = rect().height()-rect().y();
        diffX *= cos( rotation() * PI / 180.0 );
        diffY *= sin( rotation() * PI / 180.0 );
        setPos(x() - diffX, y() - diffY);
        // ToDo: check calculations
        scene_->setSceneRect(scene_->sceneRect().x()-diffX, scene_->sceneRect().y()-diffY, scene_->sceneRect().width(), scene_->sceneRect().height());
    }
    else if(event->key() == Qt::Key_Space)
    {
        qDebug() << "Space";
        // shoot
    }
}
