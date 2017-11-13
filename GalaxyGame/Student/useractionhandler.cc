#include "useractionhandler.hh"

#include <QDebug>

Student::UserActionHandler::UserActionHandler(QObject* parent) : QObject(parent)
{

}


Student::UserActionHandler::~UserActionHandler()
{

}

void Student::UserActionHandler::travelToStarSystemRequest(unsigned idStarUi)
{
    emit travelRequest(idStarUi);
}

void Student::UserActionHandler::showStarSystemGoods(unsigned idStarUi)
{
    emit showGoodsInfo(idStarUi);
}

void Student::UserActionHandler::pressedSpace()
{
    emit tradeRequest();
}

void Student::UserActionHandler::pressedPlayerMovementKey(QGraphicsPixmapItem *shipUi, int x, int y)
{
    emit playerMovedInSS(shipUi, x, y);
}

