#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <memory>

#include "starsystem.hh"
#include "starsystemui.hh"
#include "useractionhandler.hh"
#include "igalaxy.hh"

//! QList of QPairs used to store StarSystem base objects and their StarSystemUi UI representations
typedef QList< QPair<std::shared_ptr<Common::StarSystem>, Student::StarSystemUi*> > starSystemUI_t;

namespace Ui {
class MapWindow;
}

/**
 * @brief MapWindow represents overall view of all Star Systems, shows basic information
 * about them and allows player to travel among Star Systems
 */
class MapWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param handler Handler which is used to get actions from user and forward them further
     * @param starSystem vector of all Star Systems in galaxy
     * @param currentStarSystem Star System containing PlayerShip object
     * @param parent parent QObject
     */
    explicit MapWindow(std::shared_ptr<Student::UserActionHandler> handler,
                       Common::StarSystem::StarSystemVector starSystem,
                       std::shared_ptr<Common::StarSystem> currentStarSystem,
                       QWidget *parent = 0);
    /**
     * @brief Destructor.
     */
    ~MapWindow();

    /**
     * @brief setPlanetsByStarSystem
     * @param planets planet vector to be stored here
     * @post Exception guarantee: nothrow
     */
    void setPlanetsByStarSystem(Common::IGalaxy::ShipVector planets) {planets_ = planets;}

    /**
     * @brief markStarSystemAsDistressed
     * @param starSystem Star System containing distressed ship
     * @exception throws UnknownStarSystemException if starSystem is not found in starSystemList_ vector
     * @post Exception guarantee: strong
     * @post starSystem is marked in UI with pixDistressed_ icon
     */
    void markStarSystemAsDistressed(std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @brief unmarkStarSystemDistress
     * @param starSystem Star System freed of distressed ships
     * @exception throws UnknownStarSystemException if starSystem is not found in starSystemList_ vector
     * @post Exception guarantee: strong
     * @post pixDistressed_ icon in UI is removed from starSystem
     */
    void unmarkStarSystemDistress(std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @brief addMarkSign adds mark to item
     * @param item QGraphicsPixmapItem which is supposed to be marked
     * @param pixmap QPixmap which is set to the mark
     * @param x x coordinate of item
     * @param y y coordinate of item
     * @post Exception guarantee: nothrow
     * @post if item is not nullptr, pixmap is set to item and put to scene
     * according to x and y coordinates
     */
    void addMarkSign(QGraphicsPixmapItem *item, QPixmap pixmap, int x, int y);
private:
    //! MapWindow ui
    Ui::MapWindow *ui;

    //! Handler which is used to get actions from user and forward them further
    std::shared_ptr<Student::UserActionHandler> handler_ = nullptr;

    //! Scene where all drawable objects in MapWindow are added
    QGraphicsScene *scene_ = nullptr;

    //! Paired list of base StarSystem objects and their StarSystemUi UI representatios
    starSystemUI_t starSystemList_;

    //! Current planets from certain Star System used for indo view of Star System
    Common::IGalaxy::ShipVector planets_;

    //! coordsScale_ are used to scale course side coordinates to make the scene "bigger"
    int coordsScale_ = 30;

    //! distressedStarSystemItems_ stores QGraphicsPixmapItems representing StarSystems in distress
    std::vector<QGraphicsPixmapItem*> distressedStarSystemItems_;

    //! playerLocation_ is QGraphicsPixmapItem representing player's position in galaxy
    QGraphicsPixmapItem* playerLocation_ = nullptr;

    //! pixmap used to create QGraphicsPixmapItem to mark distressed StarSystems
    QPixmap pixDistressed_;

    //! pixmap used to set to NPCShipUi when ship is abandoned
    QPixmap pixAbandoned_;

    /**
     * @brief showStarSystems creates UI representation for base StarSystem objects, pairs them and stores in starSystemList_
     * @param starSystem Vector of all starSystems in galaxy
     * @post UI representation of all starSystems is created, paired with it's base object and stored in starSystemList_
     * @post Exception guarantee: nothrow
     */
    void showStarSystems(Common::StarSystem::StarSystemVector starSystem);
public Q_SLOTS:

    /**
     * @brief travelToStarSystem changes position of QGraphicsPixmapItem playerLocation_ in map
     * @param idStarUi id of Star System
     * @exception trows UnknownStarSystemException if Star System with id idStarUi was not found
     * @post Exception guarantee: strong
     */
    void travelToStarSystem(unsigned idStarUi);

    /**
     * @brief showGoodsInfo shows info about StarSystem in right info panel
     * @param idStarUi id of Star System
     * @post Info about Star System, it's planets and goods is shown to player
     * @post Exception guarantee: nothrow
     */
    void showGoodsInfo(unsigned idStarUi);

Q_SIGNALS:
    //! Request for planets_ to be updated according to given Star System id
    void planetsByStarSystemRequest(unsigned id);
};

#endif // MAPWINDOW_H
