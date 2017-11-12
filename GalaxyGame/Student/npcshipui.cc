#include "npcshipui.hh"

#include <QDebug>

NPCShipUi::NPCShipUi(QPixmap pixmap)
{  
    setPixmap(pixmap);
    setScale(0.2);
    setTransformOriginPoint(static_cast<int>(scale()*boundingRect().size().width()/2), static_cast<int>(scale()*boundingRect().size().height()/2));

    int posX = Common::randomMinMax(-500, 500);
    int posY = Common::randomMinMax(-500, 500);

    coordinates_ = Common::Point(posX, posY);

    setPos(posX, posY);
}

