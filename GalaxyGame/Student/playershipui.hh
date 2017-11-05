#ifndef PLAYERSHIPUI_H
#define PLAYERSHIPUI_H

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

class PlayerShipUi : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PlayerShipUi(QPixmap pixmap, QObject *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private Q_SLOTS:
    void updateMovement();

Q_SIGNALS:
    void pressedSpace();

private:
    void goLeft();
    void goRight();
    void goUp(qreal width, qreal height);
    void goDown(qreal width, qreal height);
    QSet<int> pressedKeys;
    QTimer *keyMovement = nullptr;
    void moveAccordingToPressedKey(int key);
};

#endif // PLAYERSHIPUI_H
