#include "drawableobjectsmanager.hh"
#include "planet.hh"
#include "cargoship.hh"
#include "utility"
#include "unknownshipexception.hh"

#include <qdebug.h>
#include <QPainter>
#include <QBrush>
#include <cassert>

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

    shipAbandonedIcon_ = QPixmap(":/images/images/dead.png");
}

Student::StarSystemScene* Student::DrawableObjectsManager::getScene()
{
    assert(scene_);

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
    assert(scene_);

    return scene_->collidingItems(player);
}


void Student::DrawableObjectsManager::registerShip(std::shared_ptr<Common::Ship> ship)
{
    if( std::dynamic_pointer_cast<Student::Planet> (ship))
    {
        int randomPlanetIndex = Common::randomMinMax(0, planets_.size()-1);
        QString randomPlanetName = QString::fromStdString(planets_.at(randomPlanetIndex));
        QString pathToImage = QString(":/images/images/planets/%1.png").arg(randomPlanetName.toLower());
        QPixmap bigPixmap = QPixmap(pathToImage);
        Student::PlanetUi *planet = new Student::PlanetUi(bigPixmap.scaledToWidth(bigPixmap.width()/3),
                                                          ship->getLocation()->getCoordinates().x*coordsScale_+
                                                            Common::randomMinMax(starSystemSpawnRadius_*(-1), starSystemSpawnRadius_-bigPixmap.width()/3),
                                                          ship->getLocation()->getCoordinates().y*coordsScale_+
                                                            Common::randomMinMax(starSystemSpawnRadius_*(-1), starSystemSpawnRadius_-bigPixmap.height()/3));
        planetUiList_.append(qMakePair(std::dynamic_pointer_cast<Student::Planet> (ship), planet));
    }

    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        NPCShipUi *npcship = new NPCShipUi(cargoShipIcon_,
                                           ship->getLocation()->getCoordinates().x*coordsScale_+
                                            Common::randomMinMax(starSystemSpawnRadius_*(-1), starSystemSpawnRadius_),
                                           ship->getLocation()->getCoordinates().y*coordsScale_+
                                            Common::randomMinMax(starSystemSpawnRadius_*(-1), starSystemSpawnRadius_));
        cargoShipUiList_.append(qMakePair(std::dynamic_pointer_cast<Common::CargoShip> (ship), npcship));
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship))
    {
        PlayerShipUi *playership = new PlayerShipUi(playerShipIcon_,
                                                    ship->getLocation()->getCoordinates().x*coordsScale_,
                                                    ship->getLocation()->getCoordinates().y*coordsScale_,
                                                    userActionHandler_);
        playerShipUiList_.append(qMakePair(std::dynamic_pointer_cast<PlayerShip> (ship), playership));
    }
    else
    {
        throw UnknownShipException("Ship " + ship->getName() + " doesn't have a known type.");
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
                return;
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
                return;
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
                return;
            }
        }
    }
    else
    {
        throw UnknownShipException("Ship " + ship->getName() + " doesn't have a known type.");
    }
    throw UnknownShipException("Ship " + ship->getName() + " isn't registered in UI.");
}

void Student::DrawableObjectsManager::changeShipUiPosition(QGraphicsPixmapItem *shipUi, int x, int y)
{
    setPosition(shipUi, x, y);
}

void Student::DrawableObjectsManager::clearScene()
{
    assert(scene_);

    scene_->eraseEverything();
}

void Student::DrawableObjectsManager::drawShip(std::shared_ptr<Common::Ship> ship)
{
    assert(scene_);

    if( std::dynamic_pointer_cast<Student::Planet> (ship))
    {
        for(auto element : planetUiList_)
        {
            if(element.first == ship)
            {
                scene_->drawPlanet(element.second);
                return;
            }
        }
        throw UnknownShipException("Planet " + ship->getName() + " isn't registered in UI.");
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        for(auto element : cargoShipUiList_)
        {
            if(element.first == ship)
            {
                scene_->drawNPCShip(element.second);
                return;
            }
        }
        throw UnknownShipException("CargoShip " + ship->getName() + " isn't registered in UI.");
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship))
    {
        for(auto element : playerShipUiList_)
        {
            if(element.first == ship)
            {
                scene_->drawPlayerShip(element.second);
                element.second->setFocus();
                return;
            }
        }
        throw UnknownShipException("Player " + ship->getName() + " isn't registered in UI.");
    }
    else
    {
        throw UnknownShipException("Ship " + ship->getName() + " doesn't have known type and isn't registered in UI.");
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

std::shared_ptr<Common::CargoShip> Student::DrawableObjectsManager::getCargoShipByUiItem(QGraphicsItem* item)
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


NPCShipUi* Student::DrawableObjectsManager::getShipUiByObject(std::shared_ptr<Common::Ship> ship)
{
    for(auto element : cargoShipUiList_)
    {
        if(element.first == (ship))
        {
            return element.second;
        }
    }
    return nullptr;
}

void Student::DrawableObjectsManager::setFocusOnPlayer(std::shared_ptr<PlayerShip> ship)
{
    for(auto element : playerShipUiList_)
    {
        if(element.first == ship)
        {
            scene_->setFocusItem(element.second);
            return;
        }
    }
    throw UnknownShipException("PlayerShip " + ship->getName() + " isn't registered in UI.");
}

void Student::DrawableObjectsManager::changeShipPosition(std::shared_ptr<Common::Ship> ship, Common::Point from, Common::Point to)
{
    if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        NPCShipUi* uiShip = getShipUiByObject(std::dynamic_pointer_cast<Common::CargoShip> (ship));
        if(uiShip != nullptr)
        {
            uiShip->setPos(to.x*coordsScale_, to.y*coordsScale_);
            if(!isInPlayerShipVisibilityRange(uiShip) && scene_->isNPCShipVisible(uiShip))
            {
                scene_->eraseNPCShip(uiShip);
            }
        }
        else
        {
            throw UnknownShipException("Ship " + ship->getName() + " isn't registered in UI.");
        }
    }
    else
    {
        throw UnknownShipException("Ship " + ship->getName() + " doesn't have known type");
    }
}

void Student::DrawableObjectsManager::changeShipPosition(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem)
{    
    assert(scene_);

    if(std::dynamic_pointer_cast<Common::CargoShip> (ship))
    {
        NPCShipUi* uiShip = getShipUiByObject(std::dynamic_pointer_cast<Common::CargoShip> (ship));
        if(uiShip != nullptr)
        {
            if(ship->getLocation() != nullptr)
            {
                uiShip->setPos(ship->getLocation()->getCoordinates().x*coordsScale_, ship->getLocation()->getCoordinates().y*coordsScale_);

                if(!isInPlayerShipVisibilityRange(uiShip) && scene_->isNPCShipVisible(uiShip))
                {
                    scene_->eraseNPCShip(uiShip);
                }
                else if (isInPlayerShipVisibilityRange(uiShip) && !scene_->isNPCShipVisible(uiShip))
                {
                    scene_->drawNPCShip(uiShip);
                }
            }
            else
            {
                //If realocated ship doesn't have position, it is "lost" somewhere in galaxy
                //But ship can also have previous StarSystem location nullptr => in can be lost
                //for a while but found again. So Let the ship stay in the Galaxy, just erase in
                //case it is visible.

                if(scene_->isNPCShipVisible(uiShip))
                {
                    scene_->eraseNPCShip(uiShip);
                }
            }
        }
        else
        {
            throw UnknownShipException("Ship " + ship->getName() + " isn't registered in UI.");
        }

    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship))
    {
        PlayerShipUi* uiShip = getPlayerShipUiByObject(std::dynamic_pointer_cast<PlayerShip> (ship));
        if(uiShip != nullptr)
        {
            QRect rect = QRect(ship->getLocation()->getCoordinates().x*coordsScale_-starSystemSpawnRadius_,
                                 ship->getLocation()->getCoordinates().y*coordsScale_-starSystemSpawnRadius_,
                                 starSystemSpawnRadius_*2, starSystemSpawnRadius_*2);
            scene_->setSceneRect(rect);

            if(ship->getLocation() != nullptr)
            {
                setPosition(uiShip, ship->getLocation()->getCoordinates().x*coordsScale_, ship->getLocation()->getCoordinates().y*coordsScale_);
            }
        }
        else
        {
            throw UnknownShipException("Player ship " + ship->getName() + " isn't registered in UI.");
        }
    }
    else
    {
        throw UnknownShipException("Player ship " + ship->getName() + " doesn't have known type");
    }
}


bool Student::DrawableObjectsManager::isInPlayerShipVisibilityRange(NPCShipUi* ship)
{
    assert(playerShipUiList_.size() > 0);

    //ToDo: select which playership -- playerShipUiList_.at(0) is not correct solution (but in current state enough)
    return Common::distance(ship->pos().x(), ship->pos().y(), playerShipUiList_.at(0).second->pos().x(),
                            playerShipUiList_.at(0).second->pos().y()) > visibilityRange_;
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

void Student::DrawableObjectsManager::shipIsAbandoned(std::shared_ptr<Common::Ship> ship)
{
    NPCShipUi* shipUi = getShipUiByObject(ship);
    if(shipUi != nullptr)
    {
        shipUi->changePixmapAndRotation(shipAbandonedIcon_, 0);
    }
    else
    {
        throw UnknownShipException("Ship " + ship->getName() + "  isn't registered in UI.");
    }
}

void Student::DrawableObjectsManager::setPosition(QGraphicsPixmapItem *item, int x, int y)
{
    assert(scene_);

    if(y < scene_->sceneRect().top()+scene_->sceneRect().height()-item->pixmap().height() && x > scene_->sceneRect().left() &&
            y > scene_->sceneRect().top() && x < scene_->sceneRect().left()+scene_->width()-item->pixmap().width())
    {
        item->setPos(x, y);
    }
    else
    {
        qDebug() << "out of SS";
    }
}
