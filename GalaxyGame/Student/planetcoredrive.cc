#include "planetcoredrive.hh"

#include <assert.h>

PlanetCoreDrive::PlanetCoreDrive(std::shared_ptr<Common::IGalaxy> galaxy):
    ShipEngine(MAX_HEALTH), galaxy_(galaxy)
{

}

PlanetCoreDrive::~PlanetCoreDrive()
{

}

void PlanetCoreDrive::onStart()
{
    //it never starts, it's a planet!
}

Common::StarSystem::StarSystemVector PlanetCoreDrive::getValidDestinations(std::shared_ptr<Common::StarSystem> source) const
{
    return Common::StarSystem::StarSystemVector();
}

bool PlanetCoreDrive::isValidTrip(std::shared_ptr<Common::StarSystem> source,
                            std::shared_ptr<Common::StarSystem> destination) const
{
    return false;
}

int PlanetCoreDrive::requiredTurns(std::shared_ptr<Common::StarSystem> source,
                         std::shared_ptr<Common::StarSystem> destination) const
{
    return 0;
}
