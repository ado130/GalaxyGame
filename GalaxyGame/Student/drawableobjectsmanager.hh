#ifndef DRAWABLEOBJECTSMANAGER_HH
#define DRAWABLEOBJECTSMANAGER_HH

#include "playershipui.hh"
#include "starsystemscene.hh"
#include "planet.hh"
#include "npcshipui.hh"
#include "cargoship.hh"
#include "playership.hh"
#include "useractionhandler.hh"

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

    DrawableObjectsManager(StarSystemScene *scene, std::shared_ptr<Student::UserActionHandler> userActionHandler, QObject *parent = 0);

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
    NPCShipUi* getCargoShipUiByObject(std::shared_ptr<Common::Ship> ship);
    void setFocusOnPlayer(std::shared_ptr<PlayerShip> ship);
    Common::IGalaxy::ShipVector getPlanetsByStarSystem(Common::IGalaxy::ShipVector ships);
    void shipIsAbandoned(std::shared_ptr<Common::Ship> ship);


public Q_SLOTS:
    void registerShip(std::shared_ptr<Common::Ship> ship);
    void unregisterShip(std::shared_ptr<Common::Ship> ship);
    void changeShipUiPosition(QGraphicsPixmapItem *shipUi, int x , int y);
    void changeShipPosition(std::shared_ptr<Common::Ship> ship, Common::Point from, Common::Point to);
    void changeShipPosition(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> oldLocation);
    void pressedSpaceSlot();
private:
    std::vector<std::string> planets = {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};
    Student::StarSystemScene *scene_;
    std::shared_ptr<Student::UserActionHandler> userActionHandler_;
    //scale used to multiply course side coordinates to create "zoom efect"
    //and starsystems won't intervene with each other
    //(just to make our scene "bigger" so it can use more space)
    int coordsScale_ = 5000;
    int starSystemSpawnRadius = 800;

    QPixmap playerShipIcon_;
    QPixmap cargoShipIcon_;
    QPixmap shipAbandonedIcon_;

    bool isInPlayerShipVisibilityRange(NPCShipUi* ship);
    void setPosition(QGraphicsPixmapItem *item, int x, int y);

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
