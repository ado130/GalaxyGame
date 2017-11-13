#include "planetui.hh"

#include <QDebug>

Student::PlanetUi::PlanetUi(QPixmap pixmap, int posX, int posY)
{
    setPixmap(pixmap);
//    setScale(0.3);

    setPos(posX, posY);
}
