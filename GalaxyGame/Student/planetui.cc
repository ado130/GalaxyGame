#include "planetui.hh"

Student::PlanetUi::PlanetUi(QPixmap pixmap)
{
    setPixmap(pixmap);
    setScale(0.3);

    int posX = Common::randomMinMax(-500, 500);
    int posY = Common::randomMinMax(-500, 500);

    coordinates_ = Common::Point(posX, posY);

    setPos(posX, posY);
}
