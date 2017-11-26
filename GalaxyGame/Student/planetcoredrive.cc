#include "planetcoredrive.hh"

#include <assert.h>
#include <QDebug>

Student::PlanetCoreDrive::PlanetCoreDrive(std::shared_ptr<Common::IGalaxy> galaxy):
    ShipEngine(MAX_HEALTH), galaxy_(galaxy)
{

}

Student::PlanetCoreDrive::~PlanetCoreDrive()
{

}

void Student::PlanetCoreDrive::onStart()
{
    //it never starts, it's a planet!
}

Common::StarSystem::StarSystemVector Student::PlanetCoreDrive::getValidDestinations(std::shared_ptr<Common::StarSystem> source) const
{
    Q_UNUSED(source);
    return Common::StarSystem::StarSystemVector();
}

bool Student::PlanetCoreDrive::isValidTrip(std::shared_ptr<Common::StarSystem> source,
                            std::shared_ptr<Common::StarSystem> destination) const
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
    return false;
}

int Student::PlanetCoreDrive::requiredTurns(std::shared_ptr<Common::StarSystem> source,
                         std::shared_ptr<Common::StarSystem> destination) const
{
    Q_UNUSED(source);
    Q_UNUSED(destination);
    return 0;
}
