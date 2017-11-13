#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include "point.hh"

#include <QGraphicsPixmapItem>
#include <QSet>
#include <QTimer>


class NPCShipUi : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NPCShipUi(QPixmap pixmap, int posX, int posY, QObject *parent = 0);

private Q_SLOTS:
    void moveForward();
    void randomChangeOfDirection();
private:
    void goLeft();
    void goRight();
    void goUp(qreal width, qreal height);
    void goDown(qreal width, qreal height);
    QTimer *keyMovement = nullptr;
    QTimer *randomKeyPress = nullptr;
};

#endif // NPCSHIP_HH
