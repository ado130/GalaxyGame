#include "starsystemscene.hh"
#include "cargoship.hh"
#include "typeinfo"
#include "string"
#include "planetui.hh"
#include "unknownshipexception.hh"

#include <QDebug>

Ui::StarSystemScene::StarSystemScene(QWidget *parent)
{
    parent_ = parent;
    setBackgroundBrush( Qt::lightGray );
}

void Ui::StarSystemScene::drawPlayerShip(PlayerShipUi *ship)
{
    playerShipList_.push_back(ship);
    addItem(ship);
}

void Ui::StarSystemScene::erasePlayerShip(PlayerShipUi *ship)
{
    std::vector<PlayerShipUi*>::iterator iter = std::find(playerShipList_.begin(), playerShipList_.end(), ship);
    if(iter != playerShipList_.end())
    {
        playerShipList_.erase(iter);
        removeItem(ship);
        return;
    }
    throw Student::UnknownShipException("UI Player ship was not found.");
}

void Ui::StarSystemScene::eraseAllPlayerShips()
{
    for(Ui::PlayerShipUi* player : playerShipList_)
    {
        removeItem(player);
    }
    playerShipList_.clear();
}

void Ui::StarSystemScene::drawNPCShip(NPCShipUi* ship)
{
    shipList_.push_back(ship);
    addItem(ship);
}

void Ui::StarSystemScene::eraseNPCShip(NPCShipUi *ship)
{
    std::vector<NPCShipUi*>::iterator iter = std::find(shipList_.begin(), shipList_.end(), ship);

    if(iter != shipList_.end())
    {
        shipList_.erase(iter);
        removeItem(ship);
        return;
    }
    throw Student::UnknownShipException("NPC ship was not found.");
}

void Ui::StarSystemScene::eraseAllNPCShips()
{
    for(Ui::NPCShipUi* ship : shipList_)
    {
        removeItem(ship);
    }
    shipList_.clear();
}

bool Ui::StarSystemScene::isNPCShipVisible(Ui::NPCShipUi* ship)
{
    if(std::find(shipList_.begin(), shipList_.end(), ship) == shipList_.end()) return false;
    return true;
}

void Ui::StarSystemScene::drawPlanet(Ui::PlanetUi *planet)
{
    planetList_.push_back(planet);
    addItem(planet);
}

void Ui::StarSystemScene::erasePlanet(Ui::PlanetUi *planet)
{
    std::vector<Ui::PlanetUi*>::iterator iter = std::find(planetList_.begin(), planetList_.end(), planet);

    if(iter != planetList_.end())
    {
        planetList_.erase(iter);
        removeItem(planet);
        return;
    }
    throw Student::UnknownShipException("Planet was not found.");
}

void Ui::StarSystemScene::eraseAllPlanets()
{
    for(Ui::PlanetUi* planet : planetList_)
    {
        removeItem(planet);
    }
    planetList_.clear();
}

bool Ui::StarSystemScene::isPlanetShipVisible(Ui::PlanetUi *ship)
{
    if(std::find(planetList_.begin(), planetList_.end(), ship) == planetList_.end()) return false;
    return true;
}

void Ui::StarSystemScene::eraseEverything()
{
    eraseAllPlanets();
    eraseAllNPCShips();
    eraseAllPlayerShips();
    clear();
}
