#ifndef PLAYERSHIPUI_H
#define PLAYERSHIPUI_H

#include "useractionhandler.hh"

#include <memory>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QSet>

namespace Ui {

/**
 * @brief Class representing PlayerShips in UI
 */
class PlayerShipUi : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param pixmap Pixmap appearance of PlayerShipUi
     * @param posX initial x coordinate
     * @param posY initial y coordinate
     * @param userActionHandler Handler which is used to get actions from user and forward them further
     * @param parent Parent QObject
     */
    PlayerShipUi(QPixmap pixmap, int posX, int posY, std::shared_ptr<Student::UserActionHandler> userActionHandler, QObject *parent = 0);
protected:
    /**
     * @brief keyPressEvent
     * @param event QKeyEvent *event
     * @post if user presses key, key is added to pressedKeys_ set and movement is updated
     * @post Exception guarantee: nothrow
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief keyReleaseEvent
     * @param event QKeyEvent *event
     * @post if user release key, key is removed from pressedKeys_ set
     * @post Exception guarantee: nothrow
     */
    void keyReleaseEvent(QKeyEvent *event);
private:
    //! pressedKeys_ is keeping track of important keys which user presses
    QSet<int> pressedKeys_;

    //! keyMovement_ is a timer which updates PlayerShipUi coordinates periodically
    QTimer *keyMovement_ = nullptr;

    //! Handler which is used to get actions from user and forward them further
    std::shared_ptr<Student::UserActionHandler> handler_;

    /**
     * @brief goLeft sets rotation of ship counter-clockwise
     * @post ship changes it's rotation by 5 degrees counter-clockwise
     * @post Exception guarantee: nothrow
     */
    void goLeft();

    /**
     * @brief goRight sets rotation of ship clockwise
     * @post ship changes it's rotation by 5 degrees clockwise
     * @post Exception guarantee: nothrow
     */
    void goRight();

    /**
     * @brief goUp calculates ship position for "moving forward" and informs handler_ about movement change
     * @post handler_ is informed about movement change
     * @pre handler_ is asociated with this object
     * @post Exception guarantee: nothrow
     */
    void goUp(qreal width, qreal height);

    /**
     * @brief goDown calculates ship position for "moving backwards" and informs handler_ about movement change
     * @pre handler_ is asociated with this object
     * @post handler_ is informed about movement change
     * @post Exception guarantee: nothrow
     */
    void goDown(qreal width, qreal height);

    /**
     * @brief moveAccordingToPressedKey invokes actions to attain desired movement according to pressed key
     * @param key Pressed key
     * @pre handler_ is asociated with this object
     * @post Exception guarantee: nothrow
     */
    void moveAccordingToPressedKey(int key);

private Q_SLOTS:
    /**
     * @brief updateMovement goes through pressedKeys_ vector and calls moveAccordingToPressedKey() method for each key
     * @post Exception guarantee: nothrow
     */
    void updateMovement();
};
}

#endif // PLAYERSHIPUI_H
