#ifndef STARSYSTEMSCENE_H
#define STARSYSTEMSCENE_H

#include "npcshipui.hh"
#include "planetui.hh"
#include "ship.hh"

#include <QGraphicsScene>

namespace Student {
class StarSystemScene : public QGraphicsScene
{
public:
    StarSystemScene(QWidget *parent = 0);

    PlanetUi *gePlanetUiByItem(QGraphicsItem *item);
    QGraphicsItem *getSceneShip(std::shared_ptr<Common::Ship> ship);

    void drawShip(NPCShipUi *ship);
    void eraseShip(NPCShipUi *ship);
    void eraseAllShips();

    void drawPlanet(PlanetUi *planet);
    void erasePlanet(PlanetUi *planet);
    void eraseAllPlanets();

    void eraseEverything();
private:
    std::vector<NPCShipUi*> shipList_;
    std::vector<PlanetUi*> planetList_;
};
}

#endif // STARSYSTEMSCENE_H
