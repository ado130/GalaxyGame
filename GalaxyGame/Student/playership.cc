#include "playership.hh"
#include "starplanet.hh"
#include "bullet.hh"

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
        bool bTrading = false;
        QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(this);
        for(int i = 0, n = colliding_Items.size(); i<n; ++i)
        {
            if(typeid (*(colliding_Items[i])) == typeid (StarPlanet))
            {
                qDebug() << "Yes, you are next to the planet";
                bTrading = true;
            }
        }

        // You can not shoot during trading
        if(bTrading) return;
        Bullet *bullet1 = new Bullet(scene_);
        bullet1->setRotation(rotation());
        bullet1->setPos(x()+width/2,y());
        scene_->addItem(bullet1);

        Bullet *bullet2 = new Bullet(scene_);
        bullet2->setRotation(rotation());
        bullet2->setPos(x()+width+width/2,y());
        scene_->addItem(bullet2);
    }
}
