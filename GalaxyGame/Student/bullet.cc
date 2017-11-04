#include "bullet.hh"
#include "npcshipui.hh"

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

Bullet::Bullet()
{
    bulletTrain_ = 0;

    setPixmap(QPixmap(":/images/images/bullet.png"));
    setScale(0.3);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move()
{
    qreal diffX = 10 * cos( (rotation()-90) * M_PI / 180.0 ) * 1.2;
    qreal diffY = 10 * sin( (rotation()-90) * M_PI / 180.0 ) * 1.2;

    setPos(x()+diffX, y()+diffY);
    bulletTrain_++;

    if(bulletTrain_ == 50)     // I know I know, just magic number, but we have to remove bullet, at least once - memory leak ;)
    {
        delete this;
    }
}
