#ifndef STARSYSTEMUI_HH
#define STARSYSTEMUI_HH

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMouseEvent>

#include "starsystem.hh"
#include "point.hh"
#include "useractionhandler.hh"

namespace Student {
/**
 * @brief Class representing StarSystems in map UI
 */
class StarSystemUi : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Constructor
     * @param pixmap Pixmap appearance of StarSystemUi
     * @param handler Handler which is used to get actions from user and forward them further
     * @param position Point containing position of StarSystem
     * @param id Star System id
     */
    StarSystemUi(QPixmap pixmap, std::shared_ptr<Student::UserActionHandler> handler, Common::Point position, unsigned id);
protected:
    /**
     * @brief mousePressEvent
     * @param event QKeyEvent *event
     * @post handler_ is informed about action and show star system info
     * @post Exception guarantee: nothrow
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief mousePressEvent
     * @param event QKeyEvent *event
     * @post handler_ is informed about action and initialize player travel
     * @post Exception guarantee: nothrow
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    //! Handler which is used to get actions from user and forward them further
    std::shared_ptr<Student::UserActionHandler> handler_ = nullptr;

    //! StarSystem's id
    unsigned id_ = 0;
};
}

#endif // STARSYSTEMUI_HH
