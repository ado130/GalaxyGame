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

//! QList of QPairs used to store CargoShip base objects and their NPCShipUi UI representations
typedef QList< QPair<std::shared_ptr<Common::CargoShip>, NPCShipUi*> > cargoShipUiPair;

//! QList of QPairs used to store Planet base objects and their PlanetUi UI representations
typedef QList< QPair<std::shared_ptr<Student::Planet>, Student::PlanetUi*> > planetUiPair;

//! QList of QPairs used to store PlayerShip base objects and their PlayerShipUi UI representations
typedef QList< QPair<std::shared_ptr<PlayerShip>, PlayerShipUi*> > playerShipUiPair;

namespace Student {

/**
 * @brief DrawableObjectsManager is used to handle adding / removing / updating all objects
 * in Star System view. It is responsible for creating UI representation for every base object
 * in game which is to be shown in Star System view and pair it with it's base object.
 */
class DrawableObjectsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     * @param scene Scene on which objects are drawn
     * @param userActionHandler Handler which is used to get actions from user and forward them further
     * @param parent parent QObject
     */
    DrawableObjectsManager(StarSystemScene *scene, std::shared_ptr<Student::UserActionHandler> userActionHandler, QObject *parent = 0);

    /**
     * @brief Returns scene of Star System view
     * @pre StarSystemScene scene_ has been associated with this object
     */
    Student::StarSystemScene* getScene();

    /**
     * @brief getNumberOfShips
     * @return Number of NPC ships in Star System view
     * @post Exception guarantee: nothrow
     */
    int getNumberOfShips();

    /**
     * @brief getNumberOfPlanets
     * @return Number of Planets in Star System view
     * @post Exception guarantee: nothrow
     */
    int getNumberOfPlanets();

    /**
     * @brief getCollidingItems
     * @param player Current playership
     * @return QList of all QGraphicsItems* colliding with player
     * @pre StarSystemScene scene_ has been associated with this object
     * @post Exception guarantee: nothrow
     */
    QList<QGraphicsItem *> getCollidingItems(PlayerShipUi *player);

    /**
     * @brief clearScene erases everything from Star System view
     * @pre StarSystemScene scene_ has been associated with this object
     * @post Exception guarantee: nothrow
     */
    void clearScene();

    /**
     * @brief drawShip adds Ship object to scene
     * @param ship Ship to be added to scene
     * @exception throws UnknownShipException if ship cannot be found in registered ships lists
     * @pre StarSystemScene scene_ has been associated with this object
     * @post Exception guarantee: strong
     */
    void drawShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief getPlanetByUiItem searches for base planet object according to it's UI representation
     * @param item QGraphicsItem object representing planet
     * @return pointer to Planet object, if planet is not found nullptr is returned
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Planet> getPlanetByUiItem(QGraphicsItem *item);

    /**
     * @brief getCargoShiptByUiItem searches for base cargoShip object according to it's UI representation
     * @param item QGraphicsItem object representing cargoShip
     * @return pointer to CargoShip object, if planet is not found nullptr is returned
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Common::CargoShip> getCargoShipByUiItem(QGraphicsItem* item);

    /**
     * @brief getPlayerShipUiByObject searches for PlayerShipUi (UI object representation) of certain playerShip
     * @param ship PlayerShip base object
     * @return pointer to PlayerShipUi object, if playerShip not found nullptr is returned
     * @post Exception guarantee: nothrow
     */
    PlayerShipUi* getPlayerShipUiByObject(std::shared_ptr<PlayerShip> ship);

    /**
     * @brief getShipUiByObject searches for UI object representation of certain ship
     * @param ship Ship base object
     * @return pointer to NPCShipUi object, if playerShip not found nullptr is returned
     * @post Exception guarantee: nothrow
     */
    NPCShipUi* getShipUiByObject(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief setFocusOnPlayer
     * @param ship PlayerShip base object
     * @exception throws UnknownShipException if playerShip cannot be found in registered players list
     * @post PlayerShipUI paired with PlayerShip has focus in scene
     * @post Exception guarantee: strong
     */
    void setFocusOnPlayer(std::shared_ptr<PlayerShip> ship);

    /**
     * @brief getPlanetsByStarSystem
     * @param ships all Ships of all types in Galaxy
     * @return ShipVector of all Planets in Galaxy, empty ShipVector if no Planet is found
     * @post Exception guarantee: nothrow
     */
    Common::IGalaxy::ShipVector getPlanetsByStarSystem(Common::IGalaxy::ShipVector ships);

    /**
     * @brief shipIsAbandoned changes pixmap of NPCShipUi representation of ship to shipAbandonedIcon_
     * @param ship Ship which pixmap is to be changed
     * @exception throws UnknownShipException if ship cannot be found in registered ships list
     * @post NPCShipUi paired with ship changes it's appearance to shipAbandonedIcon_
     * @post Exception guarantee: strong
     */
    void shipIsAbandoned(std::shared_ptr<Common::Ship> ship);


public Q_SLOTS:
    /**
     * @brief registerShip creates UI representation for base ship object, pairs them and stores in lists of registered objects
     * @param ship Ship which is to be registered
     * @exception throws UnknownShipException if type of ship isn't recognized
     * @post UI representation of ship is created, paired with it's base object and stored in registered objects list
     * @post Exception guarantee: strong
     */
    void registerShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief unregisterShip removes ship and it's UI representation from registered ships list
     * @param ship Ship which is to be unregistered
     * @exception throws UnknownShipException if type of ship isn't recognized or isn't found in registered ships list
     * @post UI representation of ship is created, paired with it's base object and stored in registered objects list
     * @post Exception guarantee: strong
     */
    void unregisterShip(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief changeShipUiPosition changes position of object in scene
     * @param shipUi QGraphicsPixmapItem which is to be moved
     * @param x x coordinate of destination
     * @param y y coordinate of destination
     * @post shipUi's position is changed according to x and y coordinates.
     */
    void changeShipUiPosition(QGraphicsPixmapItem *shipUi, int x , int y);

    /**
     * @brief changeShipPosition changes position of UI representation of ship object in scene
     * @param ship base ship object
     * @param from old location Point
     * @param to destination Point
     * @exception throws UnknownShipException if type of ship isn't recognized or isn't found in registered ships list
     * @post UI representation of ship coordinates are changed according to destination Point
     * @post Exception guarantee: strong
     */
    void changeShipPosition(std::shared_ptr<Common::Ship> ship, Common::Point from, Common::Point to);

    /**
     * @brief changeShipPosition changes position of UI representation of ship object in scene
     * @param ship base ship object
     * @param oldLocation original Star System which from ship left
     * @exception throws UnknownShipException if type of ship isn't recognized or isn't found in registered ships list
     * @pre StarSystemScene scene_ has been associated with this object
     * @post UI representation of ship coordinates are changed according to current ship position
     * @post Exception guarantee: strong
     */
    void changeShipPosition(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> oldLocation);
private:
    //! planets_ are used for loading images from files
    std::vector<std::string> planets_ = {"Earth", "Jupiter", "Mars", "Mercury", "Moon", "Pluto", "Venus"};

    //! scene_ for Star System view where every game object UI representation lives
    Student::StarSystemScene *scene_;

    //! userActionHandler_ catches user actions and forwards them further
    std::shared_ptr<Student::UserActionHandler> userActionHandler_;

    //! coordsScale_ used to multiply course side coordinates to create "zoom efect" and starsystems
    //! won't intervene with each other (just to make our scene "bigger" so it can use more space)
    int coordsScale_ = 5000;

    //! starSystemSpawnRadius_ is size of side of rectangle in scene in which objects of certain
    //! Star System can be spawned with center in exact location of base starSystem*coordsScale_
    int starSystemSpawnRadius_ = 800;

    //! visibilityRange_ is distance from playerShip in which objects in scene are shown
    int visibilityRange_ = 500;

    //! playerShipIcon_ Pixmap used for playerShip representation
    QPixmap playerShipIcon_;

    //! cargoShipIcon_ Pixmap used for cargoShip representation
    QPixmap cargoShipIcon_;

    //! shipAbandonedIcon_ Pixmap used for abandoned ship representation
    QPixmap shipAbandonedIcon_;

    //! cargoShipUiList_ is used to store pairs of cargoShips base classes and it's UI representations
    cargoShipUiPair cargoShipUiList_;

    //! planetUiList_ is used to store pairs of planets base classes and it's UI representations
    planetUiPair planetUiList_;

    //! playerShipUiList_ is used to store pairs of players base classes and it's UI representations
    playerShipUiPair playerShipUiList_;

    /**
     * @brief isInPlayerShipVisibilityRange checks if NPCShipUi object distance from playerShip is
     * shorter than visibilityRange_
     * @param ship NPCShipUi object
     * @return false if ship distance from playerShip is longer than visibilityRange_, else true
     * @pre "playerShipUiList.size() > 0" at least one player is in the game
     * @post Exception guarantee: nothrow
     */
    bool isInPlayerShipVisibilityRange(NPCShipUi* ship);

    /**
     * @brief setPosition changes position of object in scene if it's in Star System
     * @param shipUi QGraphicsPixmapItem which is to be moved
     * @param x x coordinate of destination
     * @param y y coordinate of destination
     * @pre StarSystemScene scene_ has been associated with this object
     * @post shipUi's position is changed according to x and y coordinates
     * @post Exception guarantee: nothrow
     */
    void setPosition(QGraphicsPixmapItem *item, int x, int y);

Q_SIGNALS:
    /**
     * @brief pressedSpaceSignal is emited when player presses space bar key
     */
    void pressedSpaceSignal();
};
}

#endif // DRAWABLEOBJECTSMANAGER_HH
