#include "drawableobjectsmanager.hh"
#include "planet.hh"
#include "cargoship.hh"
#include "utility"

#include <qdebug.h>

//ToDo: create "IDrawableObject" do that there is no need for all the if-elses
Student::DrawableObjectsManager::DrawableObjectsManager(Student::StarSystemScene *scene, QObject *parent) :
    QObject(parent), scene_(scene)
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
        //qDebug() << "It's a planet!";
        int randomPlanetIndex = Common::randomMinMax(0, planets.size()-1);
        QString randomPlanetName = QString::fromStdString(planets.at(randomPlanetIndex));
        QString pathToImage = QString(":/images/images/planets/%1.png").arg(randomPlanetName.toLower());
        QPixmap bigPixmap = QPixmap(pathToImage);
        Student::PlanetUi *planet = new Student::PlanetUi(bigPixmap.scaledToWidth(bigPixmap.width()/3),
                                                          ship->getLocation()->getCoordinates().x*coordsScale_+
                                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius),
                                                          ship->getLocation()->getCoordinates().y*coordsScale_+
                                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius));
        planetUiList_.append(qMakePair(std::dynamic_pointer_cast<Student::Planet> (ship), planet));
    }

    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        //qDebug() << "It's a cargo!";
        NPCShipUi *npcship = new NPCShipUi(cargoShipIcon_,
                                           ship->getLocation()->getCoordinates().x*coordsScale_+
                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius),
                                           ship->getLocation()->getCoordinates().y*coordsScale_+
                                            Common::randomMinMax(starSystemSpawnRadius*(-1), starSystemSpawnRadius));
        cargoShipUiList_.append(qMakePair(std::dynamic_pointer_cast<Common::CargoShip> (ship), npcship));
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship)){
        qDebug() << "It's a player!";        
        PlayerShipUi *playership = new PlayerShipUi(playerShipIcon_,
                                                    ship->getLocation()->getCoordinates().x*coordsScale_,
                                                    ship->getLocation()->getCoordinates().y*coordsScale_);
        connect(playership, SIGNAL(pressedSpace()), this, SLOT(pressedSpaceSlot()));
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


NPCShipUi* Student::DrawableObjectsManager::getCargoShipUiByObject(std::shared_ptr<Common::CargoShip> ship)
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
    NPCShipUi* uiShip = getCargoShipUiByObject(std::dynamic_pointer_cast<Common::CargoShip> (ship));
    uiShip->setPos(to.x*coordsScale_, to.y*coordsScale_);
//    qDebug() << "NPC ship moved by " << Common::distance(from.x, from.y, to.x, to.y)*coordsScale_;
    if(!isInPlayerShipVisibilityRange(uiShip)){
        scene_->eraseNPCShip(uiShip);
    }
}

void Student::DrawableObjectsManager::changeShipPosition(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem)
{    
    if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
//        qDebug() << "NPC ship realocated!";
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
//        qDebug() << "playerShip travelled!";
        PlayerShipUi* uiShip = getPlayerShipUiByObject(std::dynamic_pointer_cast<PlayerShip> (ship));
//        scene_->setSceneRect(ship->getLocation()->getCoordinates().x*coordsScale_-starSystemRadius,
//                             ship->getLocation()->getCoordinates().y*coordsScale_-starSystemRadius,
//                             2*starSystemRadius, 2*starSystemRadius);
        if(ship->getLocation() != nullptr){
            uiShip->setPos(ship->getLocation()->getCoordinates().x*coordsScale_, ship->getLocation()->getCoordinates().y*coordsScale_);
        }
    }
}


bool Student::DrawableObjectsManager::isInPlayerShipVisibilityRange(NPCShipUi* ship)
{
    //ToDo: set range as variable
    //ToDo: select which playership -- playerShipUiList_.at(0) is not correct solution
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
    qDebug() << "draw manager presses space";
    emit pressedSpaceSignal();
}
