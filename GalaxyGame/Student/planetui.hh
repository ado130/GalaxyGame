#ifndef PLANETUI_HH
#define PLANETUI_HH

#include "point.hh"

#include <QGraphicsPixmapItem>

namespace Student {
/**
 * @brief Class representing PlanetS in UI
 *
 * @invariant PlanetUi cannot change it's position
 */
class PlanetUi : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Constructor.
     * @param pixmap Pixmap appearance of PlanetUi
     * @param posX initial x coordinate
     * @param posY initial y coordinate
     */
    PlanetUi(QPixmap pixmap, int posX, int posY);
};
}

#endif // PLANETUI_HH
