#ifndef BULLET_HH
#define BULLET_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class QGprahicsScene;

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bullet();

private:
    unsigned int bulletTrain_;

private slots:
    void move();
};

#endif // BULLET_HH
