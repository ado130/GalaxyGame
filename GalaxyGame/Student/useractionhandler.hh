#ifndef USERACTIONHANDLER_HH
#define USERACTIONHANDLER_HH

#include <QGraphicsPixmapItem>
#include <QObject>

namespace Student {
/**
 * @brief The UserActionHandler class is used for catching user's actions
 * in UI and handling them
 */
class UserActionHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief UserActionHandler
     * @param parent
     */
    UserActionHandler(QObject* parent = 0);

    /**
     * @brief Destructor
     */
    ~UserActionHandler();

    /**
     * @brief travelToStarSystemRequest
     * @param idStarUi
     * @post emits travelRequest signal
     * @post Exception guarantee: nothrow
     */
    void travelToStarSystemRequest(unsigned idStarUi);

    /**
     * @brief showStarSystemGoods
     * @param idStarUi
     * @post emits showGoodsInfo signal
     * @post Exception guarantee: nothrow
     */
    void showStarSystemGoods(unsigned idStarUi);

    /**
     * @brief pressedSpace
     * @post emits TradeRequest signal
     * @post Exception guarantee: nothrow
     */
    void pressedSpace();

    /**
     * @brief pressedPlayerMovementKey
     * @param shipUi
     * @param x x destination coordinate
     * @param y y destination coordinate
     * @post emits playerMovedInSS signal
     * @post Exception guarantee: nothrow
     */
    void pressedPlayerMovementKey(QGraphicsPixmapItem *shipUi, int x, int y);
Q_SIGNALS:
    /**
     * @brief travelRequest
     * @param idStarUi
     * @note emited when user decides to move PlayerShip to different StarSystem
     * @post Exception guarantee: nothrow
     */
    void travelRequest(unsigned idStarUi);

    /**
     * @brief showGoodsInfo
     * @param idStarUi
     * @note emited when info about StarSystem goods is needen
     * @post Exception guarantee: nothrow
     */
    void showGoodsInfo(unsigned idStarUi);

     /**
    * @brief tradeRequest
    * @note emited when user presses space bar key
    * @post Exception guarantee: nothrow
    */
    void tradeRequest();

    /**
     * @brief playerMovedInSS emited when ship changes it's location
     * @param shipUi
     * @param x
     * @param y
     * @post Exception guarantee: nothrow
     */
    void playerMovedInSS(QGraphicsPixmapItem *shipUi, int x, int y);
};
}

#endif // USERACTIONHANDLER_HH
