#include "planet.hh"

Student::Planet::Planet( std::shared_ptr<PlanetCoreDrive> engine,
                         std::shared_ptr<Common::StarSystem> starSystem,
                         std::shared_ptr<Common::IEventHandler> events) :
    Ship(engine, starSystem, events)
{

}

Student::Planet::~Planet()
{

}

std::shared_ptr<Common::IAction> Student::Planet::getAction() const
{
    return currentAction_;
}
