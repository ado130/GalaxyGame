#ifndef STARSYSTEMUI_HH
#define STARSYSTEMUI_HH

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMouseEvent>

#include "starsystem.hh"
#include "useractionhandler.hh"

namespace Student {
class StarSystemUi : public QGraphicsPixmapItem
{
public:
    StarSystemUi(std::shared_ptr<Student::UserActionHandler> handler, Common::Point position, unsigned id);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    std::shared_ptr<Student::UserActionHandler> handler_ = nullptr;
    unsigned id = 0;
};
}

#endif // STARSYSTEMUI_HH
