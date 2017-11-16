#ifndef PLAYERSHIPUI_H
#define PLAYERSHIPUI_H

#include "useractionhandler.hh"

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QSet>

class PlayerShipUi : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PlayerShipUi(QPixmap pixmap, int posX, int posY, std::shared_ptr<Student::UserActionHandler> userActionHandler, QObject *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QSet<int> pressedKeys_;
    QTimer *keyMovement_ = nullptr;
    std::shared_ptr<Student::UserActionHandler> handler_;
    void goLeft();
    void goRight();
    void goUp(qreal width, qreal height);
    void goDown(qreal width, qreal height);
    void moveAccordingToPressedKey(int key);

private Q_SLOTS:
    void updateMovement();

//Q_SIGNALS:
//    void pressedSpace();
};

#endif // PLAYERSHIPUI_H
