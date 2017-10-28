#include "galaxy.hh"
#include "stateexception.hh"
#include "objectnotfoundexception.hh"

#include <algorithm>
#include <QDebug>

Student::Galaxy::Galaxy(QObject *parent) : QObject(parent)
{
}

Student::Galaxy::~Galaxy()
{

}

void Student::Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{
    if(std::find(shipsInGalaxy_.begin(), shipsInGalaxy_.end(), ship) != shipsInGalaxy_.end())
    {
       throw Common::StateException("Ship is already in the galaxy.");
    }

    emit newShip(ship);

    shipsInGalaxy_.push_back(ship);
}

void Student::Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{
    if(std::find(shipsInGalaxy_.begin(), shipsInGalaxy_.end(), ship) != shipsInGalaxy_.end())
    {
        throw Common::ObjectNotFoundException("Ship does not exist in the galaxy.");
    }
    else
    {
        shipsInGalaxy_.erase( std::remove( shipsInGalaxy_.begin(), shipsInGalaxy_.end(), ship ),
                              shipsInGalaxy_.end() );         // erase-remove idiom
    }
}

void Student::Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    for(auto k : starSystemsInGalaxy_)
    {
        if(k->getName() == starSystem->getName() || k->getId() == starSystem->getId() || k->getCoordinates() == starSystem->getCoordinates())
        {
            throw Common::StateException("Star system is already in the galaxy.");
        }
    }

    starSystemsInGalaxy_.push_back(starSystem);
}

std::shared_ptr<Common::IGalaxy::ShipVector> Student::Galaxy::getShips()
{
    std::shared_ptr<Common::IGalaxy::ShipVector> pShipsInGalaxy = std::make_shared<Common::IGalaxy::ShipVector>(shipsInGalaxy_);
    return pShipsInGalaxy;
}

Common::StarSystem::StarSystemVector Student::Galaxy::getSystemsInRange(std::shared_ptr<Common::StarSystem> origin, int range)
{
    if(std::find(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(), origin) != starSystemsInGalaxy_.end())
    {
        throw Common::ObjectNotFoundException("Star system does not exist in the galaxy.");
    }
    else
    {
        Common::StarSystem::StarSystemVector returnStarSystemVector;
        for(auto k : starSystemsInGalaxy_)
        {
            if(k->getCoordinates().distanceTo(origin->getCoordinates()) <= range)
            {
                returnStarSystemVector.push_back(k);
            }
        }

        return returnStarSystemVector;
    }
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getRandomSystem()
{
    if(starSystemsInGalaxy_.empty())
    {
        throw Common::ObjectNotFoundException("Galaxy does not contain any star system");
    }

    return starSystemsInGalaxy_.at(Common::randomMinMax(0, starSystemsInGalaxy_.size() - 1));
}

Common::IGalaxy::ShipVector Student::Galaxy::getShipsInStarSystem(std::string name)
{
     /*auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(), [&](const Common::Ship& e)
               {
                   return e.getName() == name;
               });
     if(it == starSystemsInGalaxy_.end())
     {

     }*/
}

std::vector<std::string> Student::Galaxy::getSystemNames()
{

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemByName(std::string name)
{
    /*auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(), [&](const Common::StarSystem& e)
                   {
                       return e.getName() == name;
                   });
     if(it == starSystemsInGalaxy_.end())
     {
        throw Common::ObjectNotFoundException("There is not any galaxy with name " + name);
     }
     else
     {
         return *it;
     }*/
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemById(unsigned id)
{
    /*auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(),
                           [=](const Common::StarSystem& e)
                           {
                              return e.getId() == id;
                           });
    if(it == starSystemsInGalaxy_.end())
    {
    throw Common::ObjectNotFoundException("There is not any galaxy with id " + std::to_string(id));
    }
    else
    {
     return *it;
    }*/
}
