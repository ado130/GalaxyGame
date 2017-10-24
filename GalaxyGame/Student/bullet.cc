#include "bullet.hh"
#include "npcship.hh"

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

Bullet::Bullet(QGraphicsScene *scene)
{
    scene_ = scene;
    bulletTrain_ = 0;

    setPixmap(QPixmap(":/images/images/bullet.png"));
    setScale(0.3);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_Items = scene_->collidingItems(this);
    for(int i = 0, n = colliding_Items.size(); i<n; ++i)
    {
        if(typeid (*(colliding_Items[i])) == typeid (NPCShip))
        {
            scene_->removeItem(colliding_Items[i]);
            scene_->removeItem(this);

            delete colliding_Items[i];
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }
    }

    qreal diffX = 10 * cos( (rotation()-90) * M_PI / 180.0 );
    qreal diffY = 10 * sin( (rotation()-90) * M_PI / 180.0 );

    setPos(x()+diffX, y()+diffY);
    bulletTrain_++;

    if (bulletTrain_ == 50)     // I know I know, just magic number, but we have to remove bullet, at least once - memory leak ;)
    {
        scene_->removeItem(this);
        delete this;
    }
}
