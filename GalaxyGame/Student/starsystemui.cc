#include "starsystemui.hh"

#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

Student::StarSystemUi::StarSystemUi(std::shared_ptr<Student::UserActionHandler> handler, Common::Point position, unsigned id):
    handler_(handler), id_(id)
{
    QString icon = QString(":/images/images/deathStar.png");

    setPixmap(QPixmap(icon));
    setScale(0.3);
    setPos(position.x*50, position.y*50);
}

void Student::StarSystemUi::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    handler_->showStarSystemGoods(id_);
}

void Student::StarSystemUi::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    handler_->travelToStarSystemRequest(id_);
}
