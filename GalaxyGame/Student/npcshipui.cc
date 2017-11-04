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

void NPCShipUi::move()
{
    qreal width = scale()*boundingRect().size().width()/2;
    qreal height = scale()*boundingRect().size().height()/2;

    int randomMove = rand() % 2 + 2;
    int randomRotation = rand() % 361 - 180;
    if(randomMove == 0)
    {
        setRotation(rotation()-randomRotation);
    }
    else if(randomMove == 1)
    {
        setRotation(rotation()+randomRotation);
    }
    else if(randomMove == 2)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 );
        setPos(x() + diffX, y() + diffY);
    }
    else if(randomMove == 3)
    {   // ToDo: movement is not correct
        qreal diffX = width * cos( (rotation()-90) * M_PI / 180.0 );
        qreal diffY = height * sin( (rotation()-90) * M_PI / 180.0 );
        setPos(x() - diffX, y() - diffY);
    }
}
