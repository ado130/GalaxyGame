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
    auto it = std::find_if(shipsInGalaxy_.begin(), shipsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::Ship>& e)
                           {
                               return e.get()->getName() == ship.get()->getName()
                                       && e.get()->getLocation() == ship.get()->getLocation()
                                       && e.get()->getEngine() == ship.get()->getEngine();
                           });

    if(it != shipsInGalaxy_.end())
    {
       throw Common::StateException("Ship is already in the galaxy.");
    }
    else
    {
        emit shipEvent(ship, true);
        shipsInGalaxy_.push_back(ship);
    }
}

void Student::Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find_if(shipsInGalaxy_.begin(), shipsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::Ship>& e)
                           {
                               return e.get()->getName() == ship.get()->getName()
                                       && e.get()->getLocation() == ship.get()->getLocation()
                                       && e.get()->getEngine() == ship.get()->getEngine();
                           });

    if(it == shipsInGalaxy_.end())
    {
        throw Common::ObjectNotFoundException("Ship does not exist in the galaxy.");
    }
    else
    {
        emit shipEvent(ship, false);
        shipsInGalaxy_.erase( std::remove( shipsInGalaxy_.begin(), shipsInGalaxy_.end(), ship ),
                              shipsInGalaxy_.end() );         // erase-remove idiom
    }
}

void Student::Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::StarSystem>& e)
                           {
                               return e.get()->getId() == starSystem.get()->getId()
                                       || e.get()->getName() == starSystem.get()->getName()
                                       || e.get()->getCoordinates() == starSystem.get()->getCoordinates();
                           });

    if(it != starSystemsInGalaxy_.end())
    {
        throw Common::StateException("Star system is already in the galaxy.");
    }
    else
    {
        starSystemsInGalaxy_.push_back(starSystem);
    }
}

std::shared_ptr<Common::IGalaxy::ShipVector> Student::Galaxy::getShips()
{
    std::shared_ptr<Common::IGalaxy::ShipVector> pShipsInGalaxy = std::make_shared<Common::IGalaxy::ShipVector>(shipsInGalaxy_);
    return pShipsInGalaxy;
}

Common::StarSystem::StarSystemVector Student::Galaxy::getSystemsInRange(std::shared_ptr<Common::StarSystem> origin, int range)
{
    auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::StarSystem>& e)
                           {
                               return e.get()->getId() == origin.get()->getId()
                                       && e.get()->getName() == origin.get()->getName()
                                       && e.get()->getCoordinates() == origin.get()->getCoordinates();
                           });

    if(it == starSystemsInGalaxy_.end())
    {
        throw Common::ObjectNotFoundException("Star system does not exist in the galaxy.");
    }
    else
    {
        Common::StarSystem::StarSystemVector returnStarSystemVector;
        for(auto k : starSystemsInGalaxy_)
        {
            if(k.get()->getCoordinates().distanceTo(origin.get()->getCoordinates()) < range
               && (k.get()->getName() != origin.get()->getName() || k.get()->getId() != origin.get()->getId() ) )
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
    auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::StarSystem>& e)
           {
               return e.get()->getName() == name;
           });
    if(it == starSystemsInGalaxy_.end())
    {
        throw Common::ObjectNotFoundException("This star system is not in galaxy.");
    }
    else
    {
        Common::IGalaxy::ShipVector returnShipVector;
        for(auto k : shipsInGalaxy_)
        {
            if(k.get()->getLocation().get()->getName() == name)
            {
                returnShipVector.push_back(k);
            }
        }

        return returnShipVector;
    }
}

std::vector<std::string> Student::Galaxy::getSystemNames()
{

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemByName(std::string name)
{
    auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::StarSystem>& e)
                           {
                               return e.get()->getName() == name;
                           });
     if(it == starSystemsInGalaxy_.end())
     {
        throw Common::ObjectNotFoundException("There is not any galaxy with name " + name);
     }
     else
     {
         return *it;
     }
}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemById(unsigned id)
{
    auto it = std::find_if(starSystemsInGalaxy_.begin(), starSystemsInGalaxy_.end(),
                           [&](const std::shared_ptr<Common::StarSystem>& e)
                           {
                              return e.get()->getId() == id;
                           });
    if(it == starSystemsInGalaxy_.end())
    {
        throw Common::ObjectNotFoundException("There is not any galaxy with id " + std::to_string(id));
    }
    else
    {
        return *it;
    }
}
