#ifndef PLANETCOREDRIVE_HH
#define PLANETCOREDRIVE_HH

#include "shipengine.hh"
#include "galaxy.hh"

class PlanetCoreDrive : public Common::ShipEngine
{
public:
    PlanetCoreDrive(std::shared_ptr<Common::IGalaxy> galaxy);
    ~PlanetCoreDrive();

    static const Health MAX_HEALTH = 100;

    bool canStart() const { return false; }

    void onStart();
    Common::StarSystem::StarSystemVector getValidDestinations(std::shared_ptr<Common::StarSystem> source) const;
    bool isValidTrip(std::shared_ptr<Common::StarSystem> source,
                     std::shared_ptr<Common::StarSystem> destination) const;
    int requiredTurns(std::shared_ptr<Common::StarSystem> source,
                      std::shared_ptr<Common::StarSystem> destination) const;
private:
    std::shared_ptr<Common::IGalaxy> galaxy_;
};

#endif // PLANETCOREDRIVE_HH
