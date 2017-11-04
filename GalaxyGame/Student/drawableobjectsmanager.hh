#ifndef DRAWABLEOBJECTSMANAGER_HH
#define DRAWABLEOBJECTSMANAGER_HH

//#include "cargoship.hh"
//#include "planet.hh"
#include "starsystemscene.hh"

#include <QObject>
#include <Qlist>

typedef QList< QPair<std::shared_ptr<Common::Ship>, NPCShipUi*> > shipUiPair;
typedef QList< QPair<std::shared_ptr<Common::Ship>, Student::PlanetUi*> > planetUiPair;

namespace Student {
class DrawableObjectsManager : public QObject
{
    Q_OBJECT
public:

    DrawableObjectsManager(StarSystemScene *scene, QObject *parent = 0);

    Student::StarSystemScene* getScene();

    void clearScene();
    void drawShip(std::shared_ptr<Common::Ship> ship);
    QGraphicsItem *getSceneShip(std::shared_ptr<Common::Ship> ship);

public Q_SLOTS:
    void registerShip(std::shared_ptr<Common::Ship> ship);
    void unregisterShip(std::shared_ptr<Common::Ship> ship);

private:
    std::vector<std::string> planets = {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};
    Student::StarSystemScene *scene_;

    shipUiPair shipUiList_;
    planetUiPair planetUiList_;
};
}

#endif // DRAWABLEOBJECTSMANAGER_HH
