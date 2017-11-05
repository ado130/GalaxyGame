#include "drawableobjectsmanager.hh"
#include "planet.hh"
#include "cargoship.hh"

#include <qdebug.h>


Student::DrawableObjectsManager::DrawableObjectsManager(Student::StarSystemScene *scene, QObject *parent) :
    QObject(parent), scene_(scene)
{

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

void Student::DrawableObjectsManager::registerShip(std::shared_ptr<Common::Ship> ship){
    if( std::dynamic_pointer_cast<Student::Planet> (ship)){
        qDebug() << "It's a planet!";

        int randomPlanetIndex = Common::randomMinMax(0, planets.size()-1);
        QString randomPlanetName = QString::fromStdString(planets.at(randomPlanetIndex));
        QString pathToImage = QString(":/images/images/planets/%1.png").arg(randomPlanetName.toLower());

        Student::PlanetUi *planet = new Student::PlanetUi(QPixmap(pathToImage));
        planetUiList_.append(qMakePair(std::dynamic_pointer_cast<Student::Planet> (ship), planet));
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
        qDebug() << "It's a cargo!";

        NPCShipUi *npcship = new NPCShipUi(QPixmap(":/images/images/NPCShip.png"));
        cargoShipUiList_.append(qMakePair(std::dynamic_pointer_cast<Common::CargoShip> (ship), npcship));
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship)){
        qDebug() << "It's a player!";

        PlayerShipUi *playership = new PlayerShipUi(QPixmap(":/images/images/playerShip.png"));
        playerShipUiList_.append(qMakePair(std::dynamic_pointer_cast<PlayerShip> (ship), playership));
    }
}

void Student::DrawableObjectsManager::unregisterShip(std::shared_ptr<Common::Ship> ship){
    if( std::dynamic_pointer_cast<Student::Planet> (ship)){
        for(int i = 0; i<planetUiList_.size(); ++i)
        {
            if(planetUiList_.at(i).first == ship)
            {
                planetUiList_.removeAt(i);
                break;
            }
        }
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
        for(int i = 0; i<cargoShipUiList_.size(); ++i)
        {
            if(cargoShipUiList_.at(i).first == ship)
            {
                cargoShipUiList_.removeAt(i);
                break;
            }
        }
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship)){
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

void Student::DrawableObjectsManager::drawShip(std::shared_ptr<Common::Ship> ship){
    if( std::dynamic_pointer_cast<Student::Planet> (ship)){
        for(auto element : planetUiList_){
            if(element.first == ship){
                scene_->drawPlanet(element.second);
            }
        }
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
        for(auto element : cargoShipUiList_){
            if(element.first == ship){
                scene_->drawNPCShip(element.second);
            }
        }
    }
    else if(std::dynamic_pointer_cast<PlayerShip> (ship)){
        for(auto element : playerShipUiList_){
            if(element.first == ship){
                scene_->drawPlayerShip(element.second);
                element.second->setFocus();
            }
        }
    }
}

std::shared_ptr<Student::Planet> Student::DrawableObjectsManager::getPlanetByUiItem(QGraphicsItem* item)
{
    for(auto element : planetUiList_){
        if(element.second == item){
            return element.first;
        }
    }
}

std::shared_ptr<Common::CargoShip> Student::DrawableObjectsManager::getCargoShiptByUiItem(QGraphicsItem* item)
{
    for(auto element : cargoShipUiList_){
        if(element.second == item){
            return element.first;
        }
    }
}

PlayerShipUi* Student::DrawableObjectsManager::getPlayerShipUiByObject(std::shared_ptr<PlayerShip> ship)
{
    for(auto element : playerShipUiList_){
        if(element.first == (ship)){
            return element.second;
        }
    }
}

void Student::DrawableObjectsManager::setFocusOnPlayer(std::shared_ptr<PlayerShip> ship)
{
    for(auto element : playerShipUiList_){
        if(element.first == ship){
            element.second->setFocus();
        }
    }
}

