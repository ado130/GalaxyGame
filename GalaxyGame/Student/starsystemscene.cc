#include "starsystemscene.hh"
#include "cargoship.hh"
#include "typeinfo"
#include "string"
#include "planetui.hh"
#include "unknownshipexception.hh"

#include <QDebug>

Student::StarSystemScene::StarSystemScene(QWidget *parent)
{
    setBackgroundBrush( Qt::lightGray );
}

void Student::StarSystemScene::drawPlayerShip(PlayerShipUi *ship)
{
    playerShipList_.push_back(ship);
    addItem(ship);
}

void Student::StarSystemScene::erasePlayerShip(PlayerShipUi *ship)
{
    std::vector<PlayerShipUi*>::iterator iter = std::find(playerShipList_.begin(), playerShipList_.end(), ship);
    if(iter != playerShipList_.end())
    {
        playerShipList_.erase(iter);
        removeItem(ship);
        return;
    }
    throw UnknownShipException("UI Player ship was not found.");
}

void Student::StarSystemScene::eraseAllPlayerShips()
{
    for(PlayerShipUi* player : playerShipList_)
    {
        removeItem(player);
    }
    playerShipList_.clear();
}

void Student::StarSystemScene::drawNPCShip(NPCShipUi* ship)
{
    shipList_.push_back(ship);
    addItem(ship);
}

void Student::StarSystemScene::eraseNPCShip(NPCShipUi *ship)
{
    std::vector<NPCShipUi*>::iterator iter = std::find(shipList_.begin(), shipList_.end(), ship);

    if(iter != shipList_.end())
    {
        shipList_.erase(iter);
        removeItem(ship);
        return;
    }
    throw UnknownShipException("UI Player ship was not found.");
}

void Student::StarSystemScene::eraseAllNPCShips()
{
    for(NPCShipUi* ship : shipList_)
    {
        removeItem(ship);
    }
    shipList_.clear();
}

bool Student::StarSystemScene::isNPCShipVisible(NPCShipUi* ship)
{
    if(std::find(shipList_.begin(), shipList_.end(), ship) == shipList_.end()) return false;
    return true;
}

void Student::StarSystemScene::drawPlanet(Student::PlanetUi *planet)
{
    planetList_.push_back(planet);
    addItem(planet);
}

void Student::StarSystemScene::erasePlanet(Student::PlanetUi *planet)
{
    std::vector<Student::PlanetUi*>::iterator iter = std::find(planetList_.begin(), planetList_.end(), planet);

    if(iter != planetList_.end())
    {
        planetList_.erase(iter);
        removeItem(planet);
        return;
    }
    throw UnknownShipException("UI Player ship was not found.");
}

void Student::StarSystemScene::eraseAllPlanets()
{
    for(Student::PlanetUi* planet : planetList_)
    {
        removeItem(planet);
    }
    planetList_.clear();
}

bool Student::StarSystemScene::isPlanetShipVisible(PlanetUi *ship)
{
    if(std::find(planetList_.begin(), planetList_.end(), ship) == planetList_.end()) return false;
    return true;
}

void Student::StarSystemScene::eraseEverything()
{
    eraseAllPlanets();
    eraseAllNPCShips();
    eraseAllPlayerShips();
    clear();
}
