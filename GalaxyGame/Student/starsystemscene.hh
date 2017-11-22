#ifndef STARSYSTEMSCENE_H
#define STARSYSTEMSCENE_H

#include "npcshipui.hh"
#include "planetui.hh"
#include "ship.hh"
#include "playershipui.hh"

#include <QGraphicsScene>

namespace Student {
/**
 * @brief StarSystemScene is a scene which holds all UI representations of
 * objects which are supposed to appear on single Star System view
 *
 * @invariant all objects stored in shipList_, planetList_ and playerShipList_
 * are visible on scene
 */
class StarSystemScene : public QGraphicsScene
{
public:
    /**
     * @brief Constructor
     * @param parent QWidget parent
     * @note creates new scene and sets it's background
     */
    StarSystemScene(QWidget *parent = 0);

    /**
     * @brief drawPlayerShip
     * @param ship PlayerUi ship to be drawn
     * @post ship appears on scene
     * @post Exception guarantee: nothrow
     */
    void drawPlayerShip(PlayerShipUi *ship);

    /**
     * @brief erasePlayerShip
     * @param ship PlayerUi ship to be erased
     * @post ship dissapears from scene
     * @post Exception guarantee: strong
     * @exception throws UnknownShipException if ship was not found
     */
    void erasePlayerShip(PlayerShipUi *ship);

    /**
     * @brief eraseAllPlayerShips
     * @post all player ships dissapears from scene
     * @post Exception guarantee: nothrow
     */
    void eraseAllPlayerShips();

    /**
     * @brief drawNPCShip
     * @param ship NPCShipUi ship to be drawn
     * @post ship appears on scene
     * @post Exception guarantee: nothrow
     */
    void drawNPCShip(NPCShipUi *ship);

    /**
     * @brief eraseNPCShip
     * @param ship NPCShipUi ship to be erased
     * @post ship dissapears from scene
     * @post Exception guarantee: nothrow
     * @exception throws UnknownShipException if ship was not found
     */
    void eraseNPCShip(NPCShipUi *ship);

    /**
     * @brief eraseAllNPCShips
     * @post all NPC ships dissapear from scene
     * @post Exception guarantee: nothrow
     */
    void eraseAllNPCShips();

    /**
     * @brief isNPCShipVisible
     * @param ship tested NPCShipUi
     * @return true if ship is visible in UI, else false
     * @post Exception guarantee: nothrow
     */
    bool isNPCShipVisible(NPCShipUi *ship);

    /**
     * @brief drawPlanet
     * @param planet PlanetUi planet to be drawn
     * @post planet appears on scene
     * @post Exception guarantee: nothrow
     */
    void drawPlanet(PlanetUi *planet);

    /**
     * @brief erasePlanet
     * @param planet PlanetUi planet to be erased
     * @post planet dissapears from scene
     * @post Exception guarantee: strong
     * @exception throws UnknownShipException if ship was not found
     */
    void erasePlanet(PlanetUi *planet);

    /**
     * @brief eraseAllPlanets
     * @post all planets dissapears from scene
     * @post Exception guarantee: nothrow
     */
    void eraseAllPlanets();

    /**
     * @brief isPlanetShipVisible
     * @param ship tested PlanetUi
     * @return true if ship is visible in UI, else false
     * @post Exception guarantee: nothrow
     */
    bool isPlanetShipVisible(PlanetUi *ship);

    /**
     * @brief eraseEverything
     * @post all objects are erased from scene
     * @post Exception guarantee: nothrow
     */
    void eraseEverything();
private:
    //! list containing all NPC ships UI representations
    std::vector<NPCShipUi*> shipList_;

    //! list containing all planets UI representations
    std::vector<PlanetUi*> planetList_;

    //! list containing all player ships UI representations
    std::vector<PlayerShipUi*> playerShipList_;

    //! parent object
    QWidget *parent_ = nullptr;
};
}

#endif // STARSYSTEMSCENE_H
