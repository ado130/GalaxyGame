#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include "point.hh"

#include <QGraphicsPixmapItem>
#include <QSet>
#include <QTimer>

namespace Ui {

/**
 * @brief Class representing NPC ships in UI
 */
class NPCShipUi : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param pixmap Pixmap appearance of NPCShipUi
     * @param posX initial x coordinate
     * @param posY initial y coordinate
     * @param parent parent QObject
     */
    NPCShipUi(QPixmap pixmap, int posX, int posY, QObject *parent = 0);

    /**
     * @brief changePixmapAndRotation
     * @param pixmap Pixmap appearance of NPCShipUi
     * @param rotation Rotation of NPCShipUi
     * @post NPCShipUi changes it's appearance according to pixmap and rotation
     * @post Exception guarantee: nothrow
     */
    void changePixmapAndRotation(QPixmap pixmap, int rotation);

    /**
     * @brief canMove
     * @param canMove bool value indicating whether ship can move
     * @pre keyMovement_ object is associated with this object
     * @pre randomKeyPress_ object is associated with this object
     * @post Exception guarantee: nothrow
     */
    void canMove(bool canMove);

    /**
     * @brief canMove
     * @return canMove_ bool value indicating whether ship can move
     * @post Exception guarantee: nothrow
     */
    bool canMove();

private Q_SLOTS:
    /**
     * @brief moveForward changes ship position forward according to current rotation
     * @post ship moved forward
     * @post Exception guarantee: nothrow
     */
    void moveForward();

    /**
     * @brief randomChangeOfDirection
     * @post ship randomly changed direction to left or right or
     * continues with previous direction
     * @post Exception guarantee: nothrow
     */
    void randomChangeOfDirection();
private:
    /**
     * @brief goLeft sets rotation of ship counter-clockwise
     * @post ship changes it's rotation random amount (0 - 180) degrees counter-clockwise
     * @post Exception guarantee: nothrow
     */
    void goLeft();

    /**
     * @brief goRight sets rotation of ship clockwise
     * @post ship changes it's rotation random amount (0 - 180) degrees clockwise
     * @post Exception guarantee: nothrow
     */
    void goRight();

    /**
     * @brief goUp sets ship position "moving forward"
     * @post ship changes it's position on x and y axis according to set rotation
     * @post Exception guarantee: nothrow
     */
    void goUp(qreal width, qreal height);

    /**
     * @brief goUp sets ship position "moving backwards"
     * @post ship changes it's position on x and y axis according to set rotation
     * @post Exception guarantee: nothrow
     */
    void goDown(qreal width, qreal height);

    //! keyMovement simulates forward key press (Up key) so that ship is still moving
    QTimer *keyMovement_ = nullptr;

    //! randomKeyPress randomly chooses left, right or none key press to change direction of ship
    QTimer *randomKeyPress_ = nullptr;

    //! canMove_ indicates whether ship can move or not
    bool canMove_;
};
}

#endif // NPCSHIP_HH
