#include "planetui.hh"

#include <QDebug>

Ui::PlanetUi::PlanetUi(QPixmap pixmap, int posX, int posY)
{
    setPixmap(pixmap);
    setPos(posX, posY);
    setZValue(-2);
}
