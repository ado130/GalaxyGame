#include "galaxy.hh"

Student::Galaxy::Galaxy()
{

}

Student::Galaxy::~Galaxy()
{

}

void Student::Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{

}

void Student::Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{

}

void Student::Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{

}

std::shared_ptr<Common::IGalaxy::ShipVector> Student::Galaxy::getShips()
{

}

Common::StarSystem::StarSystemVector Student::Galaxy::getSystemsInRange(std::shared_ptr<Common::StarSystem> origin, int range)
{

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getRandomSystem()
{

}

Common::IGalaxy::ShipVector Student::Galaxy::getShipsInStarSystem(std::string name)
{

}

std::vector<std::string> Student::Galaxy::getSystemNames()
{

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemByName(std::string name)
{

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemById(unsigned id)
{

}
