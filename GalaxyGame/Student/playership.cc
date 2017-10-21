#include "playership.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>

#define PI 3.14159265


PlayerShip::PlayerShip(std::shared_ptr<Student::Galaxy> galaxy, QGraphicsScene *scene)
{
    galaxy_ = galaxy;
    scene_ = scene;

    setPixmap(QPixmap(":/images/images/playerShip.png"));
    setScale(0.1);
    setTransformOriginPoint(QPoint(static_cast<int>(scale()*boundingRect().size().width()/2),static_cast<int>(scale()*boundingRect().size().height()/2)));
    setPos(800/2, 600/2);
}

PlayerShip::~PlayerShip()
{

}

void PlayerShip::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed";
    qreal width = scale()*boundingRect().size().width();
    qreal height = scale()*boundingRect().size().height();

    if(event->key() == Qt::Key_Left)
    {
        setRotation(rotation()-5);
    }
    else if(event->key() == Qt::Key_Right)
    {
        setRotation(rotation()+5);
    }
    else if(event->key() == Qt::Key_Up)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * PI / 180.0 );
        setPos(x() + diffX, y() + diffY);
        // ToDo: check calculations
        scene_->setSceneRect(scene_->sceneRect().x()+diffX, scene_->sceneRect().y()+diffY, scene_->sceneRect().width(), scene_->sceneRect().height());
    }
    else if(event->key() == Qt::Key_Down)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * PI / 180.0 );
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
