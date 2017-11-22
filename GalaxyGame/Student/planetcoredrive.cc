#include "planetcoredrive.hh"

#include <assert.h>
#include <QDebug>

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
    Q_UNUSED(source);
    return Common::StarSystem::StarSystemVector();
}

bool PlanetCoreDrive::isValidTrip(std::shared_ptr<Common::StarSystem> source,
                            std::shared_ptr<Common::StarSystem> destination) const
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
    return false;
}

int PlanetCoreDrive::requiredTurns(std::shared_ptr<Common::StarSystem> source,
                         std::shared_ptr<Common::StarSystem> destination) const
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
    return 0;
}
