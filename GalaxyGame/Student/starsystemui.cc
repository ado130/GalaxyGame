#include "starsystemui.hh"

#include <QDebug>

Student::StarSystemUi::StarSystemUi(std::shared_ptr<Student::UserActionHandler> handler, Common::Point position, unsigned id):
    handler_(handler), id(id)
{
    QString icon = QString(":/images/images/deathStar.png");

    setPixmap(QPixmap(icon));
    setScale(0.3);
    setPos(position.x*50, position.y*50);
}

void Student::StarSystemUi::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // ToDo: show info about starSystem
    qDebug() << "User clicked on starSystem";
}

void Student::StarSystemUi::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Travel request!";
    handler_->travelToStarSystemRequest(id);
}
