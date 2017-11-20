#include "planetui.hh"

#include <QDebug>

Student::PlanetUi::PlanetUi(QPixmap pixmap, int posX, int posY)
{
    setPixmap(pixmap);
    setPos(posX, posY);
}
