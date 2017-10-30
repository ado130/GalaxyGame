#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>

#include "ship.hh"
#include "statistics.hh"

class PlayerShip : public QObject, public Common::Ship, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    PlayerShip(QObject* parent = 0,
               std::shared_ptr<Common::ShipEngine> engine = 0,
               std::shared_ptr<Common::StarSystem> initialLocation = 0,
               std::shared_ptr<Common::IEventHandler> events = 0);

    bool decideAction();
    Student::Statistics getStatistics();

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
    Student::Statistics statistics;
    QSet<int> pressedKeys;
    QTimer *keyMovement = nullptr;
    void moveAccordingToPressedKey(int key);
};

#endif // PLAYERSHIP_H
