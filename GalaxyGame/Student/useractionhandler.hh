#ifndef USERACTIONHANDLER_HH
#define USERACTIONHANDLER_HH

#include <QGraphicsPixmapItem>
#include <QObject>

namespace Student {
class UserActionHandler : public QObject
{
    Q_OBJECT
public:
    UserActionHandler(QObject* parent = 0);
    ~UserActionHandler();
    void travelToStarSystemRequest(unsigned idStarUi);
    void showStarSystemGoods(unsigned idStarUi);
    void pressedSpace();
    void pressedPlayerMovementKey(QGraphicsPixmapItem *shipUi, int x, int y);
Q_SIGNALS:
    void travelRequest(unsigned idStarUi);
    void showGoodsInfo(unsigned idStarUi);
    void tradeRequest();
    void playerMovedInSS(QGraphicsPixmapItem *shipUi, int x, int y);
};
}

#endif // USERACTIONHANDLER_HH
