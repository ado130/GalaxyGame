#ifndef PLANETUI_HH
#define PLANETUI_HH

#include "point.hh"

#include <QGraphicsPixmapItem>

namespace Student {
class PlanetUi : public QGraphicsPixmapItem
{
public:
    PlanetUi(QPixmap pixmap, int posX, int posY);

private:
    //Coordinates in drawable scene (not StarSystem location)
//    Common::Point coordinates_ = Common::Point(0,0);
};
}

#endif // PLANETUI_HH
