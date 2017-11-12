#ifndef NPCSHIP_HH
#define NPCSHIP_HH

#include "point.hh"

#include <QGraphicsPixmapItem>


class NPCShipUi : public QGraphicsPixmapItem
{

public:
    NPCShipUi(QPixmap pixmap);

private slots:
    // Position in scene, not posiiton of starSystem
    Common::Point coordinates_ = Common::Point(0,0);
};

#endif // NPCSHIP_HH
