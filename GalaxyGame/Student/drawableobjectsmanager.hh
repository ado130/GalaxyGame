#ifndef DRAWABLEOBJECTSMANAGER_HH
#define DRAWABLEOBJECTSMANAGER_HH

#include "playershipui.hh"
#include "starsystemscene.hh"
#include "planet.hh"
#include "npcshipui.hh"
#include "cargoship.hh"
#include "playership.hh"

#include <QObject>
#include <Qlist>

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
    void setFocusOnPlayer(std::shared_ptr<PlayerShip> ship);

public Q_SLOTS:
    void registerShip(std::shared_ptr<Common::Ship> ship);
    void unregisterShip(std::shared_ptr<Common::Ship> ship);

private:
    std::vector<std::string> planets = {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};
    Student::StarSystemScene *scene_;

    cargoShipUiPair cargoShipUiList_;
    planetUiPair planetUiList_;
    playerShipUiPair playerShipUiList_;
};
}

#endif // DRAWABLEOBJECTSMANAGER_HH
