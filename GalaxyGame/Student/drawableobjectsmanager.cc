#include "drawableobjectsmanager.hh"
#include "planet.hh"
#include "cargoship.hh"
#include "utility"

#include <qdebug.h>
#include <QPainter>
#include <QBrush>

//ToDo: create "IDrawableObject" do that there is no need for all the if-elses
Student::DrawableObjectsManager::DrawableObjectsManager(Student::StarSystemScene *scene,
                                                        std::shared_ptr<Student::UserActionHandler> userActionHandler,
                                                        QObject *parent) :
    QObject(parent), userActionHandler_(userActionHandler), scene_(scene)
{
    QPixmap cargoBigIcon = QPixmap(":/images/images/NPCShip.png");
    cargoShipIcon_ = cargoBigIcon.scaledToWidth(cargoBigIcon.width());

    QPixmap playerBigIcon = QPixmap(":/images/images/playerShip.png");
    playerShipIcon_ = playerBigIcon.scaledToWidth(playerBigIcon.width()/10);
}

Student::StarSystemScene* Student::DrawableObjectsManager::getScene()
{
    return scene_;
}

int Student::DrawableObjectsManager::getNumberOfShips()
{
    return cargoShipUiList_.size();
}

int Student::DrawableObjectsManager::getNumberOfPlanets()
{
    return planetUiList_.size();
}

QList<QGraphicsItem *> Student::DrawableObjectsManager::getCollidingItems(PlayerShipUi* player)
{
    return scene_->collidingItems(player);
}


void Student::DrawableObjectsManager::registerShip(std::shared_ptr<Common::Ship> ship)
{
    if( std::dynamic_pointer_cast<Student::Planet> (ship))
    {
        int randomPlanetIndex = Common::randomMinMax(0, planets.size()-1);
        QString randomPlanetName = QString::fromStdString(planets.at(randomPlanetIndex));
        QString pathToImage = QString(":/images/images/planets/%1.png").arg(randomPlanetName.toLower());
        QPixmap bigPixmap = QPixmap(pathToImage);
        Student::PlanetUi *planet = new Student::PlanetUi(bigPixmap.scaledToWidth(bigPixmap.width()/3),
                                                          ship->getLocation()->getCoordinates().x*coordsScale_+
                                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius-bigPixmap.width()/3),
                                                          ship->getLocation()->getCoordinates().y*coordsScale_+
                                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius-bigPixmap.height()/3));
        planetUiList_.append(qMakePair(std::dynamic_pointer_cast<Student::Planet> (ship), planet));
    }

    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        NPCShipUi *npcship = new NPCShipUi(cargoShipIcon_,
                                           ship->getLocation()->getCoordinates().x*coordsScale_+
                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius),
                                           ship->getLocation()->getCoordinates().y*coordsScale_+
                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius));
        cargoShipUiList_.append(qMakePair(std::dynamic_pointer_cast<Common::CargoShip> (ship), npcship));
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship)){
        PlayerShipUi *playership = new PlayerShipUi(playerShipIcon_,
                                                    ship->getLocation()->getCoordinates().x*coordsScale_,
                                                    ship->getLocation()->getCoordinates().y*coordsScale_,
                                                    userActionHandler_);
        playerShipUiList_.append(qMakePair(std::dynamic_pointer_cast<PlayerShip> (ship), playership));
    }
}

void Student::DrawableObjectsManager::unregisterShip(std::shared_ptr<Common::Ship> ship)
{
    if( std::dynamic_pointer_cast<Student::Planet> (ship))
    {
        for(int i = 0; i<planetUiList_.size(); ++i)
        {
            if(planetUiList_.at(i).first == ship)
            {
                planetUiList_.removeAt(i);
                break;
            }
        }
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        for(int i = 0; i<cargoShipUiList_.size(); ++i)
        {
            if(cargoShipUiList_.at(i).first == ship)
            {
                cargoShipUiList_.removeAt(i);
                break;
            }
        }
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship))
    {
        for(int i = 0; i<playerShipUiList_.size(); ++i)
        {
            if(playerShipUiList_.at(i).first == ship)
            {
                playerShipUiList_.removeAt(i);
                break;
            }
        }
    }
}

void Student::DrawableObjectsManager::changeShipUiPosition(QGraphicsPixmapItem *shipUi, int x, int y)
{
    setPosition(shipUi, x, y);
}

void Student::DrawableObjectsManager::clearScene()
{
    scene_->eraseEverything();
}

void Student::DrawableObjectsManager::drawShip(std::shared_ptr<Common::Ship> ship)
{
    if( std::dynamic_pointer_cast<Student::Planet> (ship))
    {
        for(auto element : planetUiList_)
        {
            if(element.first == ship)
            {
                scene_->drawPlanet(element.second);
            }
        }
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        for(auto element : cargoShipUiList_)
        {
            if(element.first == ship)
            {
                scene_->drawNPCShip(element.second);
            }
        }
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship))
    {
        for(auto element : playerShipUiList_)
        {
            if(element.first == ship)
            {
                scene_->drawPlayerShip(element.second);
                element.second->setFocus();
            }
        }
    }
}

std::shared_ptr<Student::Planet> Student::DrawableObjectsManager::getPlanetByUiItem(QGraphicsItem* item)
{
    for(auto element : planetUiList_)
    {
        if(element.second == item)
        {
            return element.first;
        }
    }
    return nullptr;
}

std::shared_ptr<Common::CargoShip> Student::DrawableObjectsManager::getCargoShiptByUiItem(QGraphicsItem* item)
{
    for(auto element : cargoShipUiList_)
    {
        if(element.second == item)
        {
            return element.first;
        }
    }
    return nullptr;
}

PlayerShipUi* Student::DrawableObjectsManager::getPlayerShipUiByObject(std::shared_ptr<PlayerShip> ship)
{
    for(auto element : playerShipUiList_)
    {
        if(element.first == (ship))
        {
            return element.second;
        }
    }
    return nullptr;
}


NPCShipUi* Student::DrawableObjectsManager::getCargoShipUiByObject(std::shared_ptr<Common::Ship> ship)
{
    for(auto element : cargoShipUiList_){
        if(element.first == (ship)){
            return element.second;
        }
    }
    return nullptr;
}

void Student::DrawableObjectsManager::setFocusOnPlayer(std::shared_ptr<PlayerShip> ship)
{
    for(auto element : playerShipUiList_){
        if(element.first == ship){
            scene_->setFocusItem(element.second);//->setFocus();
        }
    }
}

void Student::DrawableObjectsManager::changeShipPosition(std::shared_ptr<Common::Ship> ship, Common::Point from, Common::Point to)
{
    if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
        NPCShipUi* uiShip = getCargoShipUiByObject(std::dynamic_pointer_cast<Common::CargoShip> (ship));
        uiShip->setPos(to.x*coordsScale_, to.y*coordsScale_);
        if(!isInPlayerShipVisibilityRange(uiShip)){
            scene_->eraseNPCShip(uiShip);
        }
    }

}

void Student::DrawableObjectsManager::changeShipPosition(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem)
{    
    if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
        NPCShipUi* uiShip = getCargoShipUiByObject(std::dynamic_pointer_cast<Common::CargoShip> (ship));
        if(ship->getLocation() != nullptr){
            uiShip->setPos(ship->getLocation()->getCoordinates().x*coordsScale_, ship->getLocation()->getCoordinates().y*coordsScale_);
            if(!isInPlayerShipVisibilityRange(uiShip) && scene_->isNPCShipVisible(uiShip)){
                scene_->eraseNPCShip(uiShip);
            }
            else if (isInPlayerShipVisibilityRange(uiShip) && !scene_->isNPCShipVisible(uiShip)){
                scene_->drawNPCShip(uiShip);
            }
        }
        else{
            scene_->eraseNPCShip(uiShip);
        }
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship)){
        PlayerShipUi* uiShip = getPlayerShipUiByObject(std::dynamic_pointer_cast<PlayerShip> (ship));
        QRect rect = QRect(ship->getLocation()->getCoordinates().x*coordsScale_-starSystemSpawnRadius,
                             ship->getLocation()->getCoordinates().y*coordsScale_-starSystemSpawnRadius,
                             starSystemSpawnRadius*2, starSystemSpawnRadius*2);
        scene_->setSceneRect(rect);
        if(ship->getLocation() != nullptr){
            setPosition(uiShip, ship->getLocation()->getCoordinates().x*coordsScale_, ship->getLocation()->getCoordinates().y*coordsScale_);
        }
    }
}


bool Student::DrawableObjectsManager::isInPlayerShipVisibilityRange(NPCShipUi* ship)
{
    //ToDo: set range as variable
    //ToDo: select which playership -- playerShipUiList_.at(0) is not correct solution (but in current state enough)
    return Common::distance(ship->pos().x(), ship->pos().y(), playerShipUiList_.at(0).second->pos().x(),
                            playerShipUiList_.at(0).second->pos().y()) > 1000;
}

Common::IGalaxy::ShipVector Student::DrawableObjectsManager::getPlanetsByStarSystem(Common::IGalaxy::ShipVector ships)
{
    Common::IGalaxy::ShipVector planets;
    for(auto k : ships)
    {
        if( std::dynamic_pointer_cast<Student::Planet> (k))
        {
            planets.push_back(k);
        }
    }
    return planets;
}

void Student::DrawableObjectsManager::pressedSpaceSlot()
{
    emit pressedSpaceSignal();
}

void Student::DrawableObjectsManager::setPosition(QGraphicsPixmapItem *item, int x, int y)
{

    if(y < scene_->sceneRect().top()+scene_->sceneRect().height()-item->pixmap().height() && x > scene_->sceneRect().left() &&
            y > scene_->sceneRect().top() && x < scene_->sceneRect().left()+scene_->width()-item->pixmap().width()){
        item->setPos(x, y);
    }
    else{
        qDebug() << "out of SS";
    }
}
