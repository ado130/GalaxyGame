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

void Student::DrawableObjectsManager::registerShip(std::shared_ptr<Common::Ship> ship){
    if( std::dynamic_pointer_cast<Student::Planet> (ship)){
        qDebug() << "It's a planet!";

        int randomPlanetIndex = Common::randomMinMax(0, planets.size()-1);
        QString randomPlanetName = QString::fromStdString(planets.at(randomPlanetIndex));
        QString pathToImage = QString(":/images/images/planets/%1.png").arg(randomPlanetName.toLower());

        Student::PlanetUi *planet = new Student::PlanetUi(QPixmap(pathToImage));
        planetUiList_.append(qMakePair(ship, planet));
    }
    else if(std::dynamic_pointer_cast<Common::CargoShip> (ship)){
        qDebug() << "It's a cargo!";

        NPCShipUi *npcship = new NPCShipUi(QPixmap(":/images/images/NPCShip.png"));
        shipUiList_.append(qMakePair(ship, npcship));
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
        for(int i = 0; i<shipUiList_.size(); ++i)
        {
            if(shipUiList_.at(i).first == ship)
            {
                shipUiList_.removeAt(i);
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
        for(auto element : shipUiList_){
            if(element.first == ship){
                scene_->drawShip(element.second);
            }
        }
    }
}

