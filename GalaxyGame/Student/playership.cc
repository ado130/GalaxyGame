#include "playership.hh"

#include <QDebug>
#include <cmath>
#include <QGraphicsScene>


PlayerShip::PlayerShip(std::shared_ptr<Student::Galaxy> galaxy, QGraphicsScene *scene)
{
    galaxy_ = galaxy;
    scene_ = scene;

    setPixmap(QPixmap(":/images/images/playerShip.png"));
    setScale(0.1);
    setTransformOriginPoint(static_cast<int>(scale()*boundingRect().size().width()/2), static_cast<int>(scale()*boundingRect().size().height()/2));
    //setPos(scene_->sceneRect().width() - scale()*boundingRect().size().width()/2,
          // scene_->sceneRect().height() - scale()*boundingRect().size().height()/2);
    setPos(800/2, 600/2);
}

void PlayerShip::keyPressEvent(QKeyEvent *event)
{    
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;

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
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 );
        setPos(x() + diffX, y() + diffY);
        // ToDo: check calculations
        scene_->setSceneRect(scene_->sceneRect().x()+diffX, scene_->sceneRect().y()+diffY,
                             scene_->sceneRect().width(), scene_->sceneRect().height());
    }
    else if(event->key() == Qt::Key_Down)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 );
        setPos(x() - diffX, y() - diffY);
        // ToDo: check calculations
        scene_->setSceneRect(scene_->sceneRect().x()-diffX, scene_->sceneRect().y()-diffY,
                             scene_->sceneRect().width(), scene_->sceneRect().height());
    }
    else if(event->key() == Qt::Key_Space)
    {
        qDebug() << "Space";
        // shoot
    }
}
