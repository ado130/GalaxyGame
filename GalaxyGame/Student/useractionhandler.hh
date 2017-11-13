#ifndef USERACTIONHANDLER_HH
#define USERACTIONHANDLER_HH

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
Q_SIGNALS:
    void travelRequest(unsigned idStarUi);
    void showGoodsInfo(unsigned idStarUi);
};
}

#endif // USERACTIONHANDLER_HH
