#include "starsystemui.hh"

#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <cassert>

Ui::StarSystemUi::StarSystemUi(QPixmap pixmap, std::shared_ptr<Student::UserActionHandler> handler, Common::Point position, unsigned id):
    handler_(handler), id_(id)
{
    setPixmap(pixmap);
    setPos(position.x, position.y);
}

void Ui::StarSystemUi::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    assert(handler_);

    handler_->showStarSystemGoods(id_);
}

void Ui::StarSystemUi::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    assert(handler_);

    handler_->travelToStarSystemRequest(id_);
}
