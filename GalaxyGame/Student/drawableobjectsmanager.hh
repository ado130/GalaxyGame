#ifndef DRAWABLEOBJECTSMANAGER_HH
#define DRAWABLEOBJECTSMANAGER_HH

#include "playershipui.hh"
#include "starsystemscene.hh"
#include "planet.hh"
#include "npcshipui.hh"
#include "cargoship.hh"
#include "playership.hh"

#include <QObject>
#include <QList>

typedef QList< QPair<std::shared_ptr<Common::CargoShip>, NPCShipUi*> > cargoShipUiPair;
typedef QList< QPair<std::shared_ptr<Student::Planet>, Student::PlanetUi*> > planetUiPair;
typedef QList< QPair<std::shared_ptr<PlayerShip>, PlayerShipUi*> > playerShipUiPair;

namespace Student {
class DrawableObjectsManager : public QObject
{
    Q_OBJECT
public:

    DrawableObjectsManager(StarSystemScene *scene, QObject *parent = 0);

    Student::StarSystemScene* getScene();
    int getNumberOfShips();
    int getNumberOfPlanets();
    QList<QGraphicsItem *> getCollidingItems(PlayerShipUi *player);

    void clearScene();
    void drawShip(std::shared_ptr<Common::Ship> ship);
    QGraphicsItem *getSceneShip(std::shared_ptr<Common::Ship> ship);
    std::shared_ptr<Planet> getPlanetByUiItem(QGraphicsItem *item);
    std::shared_ptr<Common::CargoShip> getCargoShiptByUiItem(QGraphicsItem* item);
    PlayerShipUi* getPlayerShipUiByObject(std::shared_ptr<PlayerShip> ship);
    NPCShipUi* getCargoShipUiByObject(std::shared_ptr<Common::CargoShip> ship);
    void setFocusOnPlayer(std::shared_ptr<PlayerShip> ship);
    Common::IGalaxy::ShipVector getPlanetsByStarSystem(Common::IGalaxy::ShipVector ships);


public Q_SLOTS:
    void registerShip(std::shared_ptr<Common::Ship> ship);
    void unregisterShip(std::shared_ptr<Common::Ship> ship);
    void changeShipPosition(std::shared_ptr<Common::Ship> ship, Common::Point from, Common::Point to);
    void changeShipPosition(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> oldLocation);
    void pressedSpaceSlot();
private:
    std::vector<std::string> planets = {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};
    Student::StarSystemScene *scene_;
    //scale used to multiply course side coordinates to create "zoom efect"
    //(just to make our scene "bigger" so it can use more space)
    int coordsScale_ = 5000;
    int starSystemRadius = 2500;
    //spawning of items in starsystem view
    int starSystemSpawnRadius = starSystemRadius/4;

    QPixmap playerShipIcon_;
    QPixmap cargoShipIcon_;

    bool isInPlayerShipVisibilityRange(NPCShipUi* ship);

    //ToDo: create generic vector + generic functions for ships -> this way, if we add new ship type,
    //we have to add functions and conditions for it
    cargoShipUiPair cargoShipUiList_;
    planetUiPair planetUiList_;
    playerShipUiPair playerShipUiList_;

Q_SIGNALS:
    void pressedSpaceSignal();
};
}

#endif // DRAWABLEOBJECTSMANAGER_HH
