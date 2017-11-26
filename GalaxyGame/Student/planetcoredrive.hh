#ifndef PLANETCOREDRIVE_HH
#define PLANETCOREDRIVE_HH

#include "galaxy.hh"

namespace Student {

/**
 * @brief PlanetCoreDrive is a type of ShipEngine that isn't able
 * to freely move.
 *
 * @invariant PlanetCoreDrive cannot ever start.
 */
class PlanetCoreDrive : public Common::ShipEngine
{
public:
    /**
     * @brief Constructor
     * @param galaxy Galaxy the engine is in
     */
    PlanetCoreDrive(std::shared_ptr<Common::IGalaxy> galaxy);

    /**
     * @brief Destructor.
     */
    ~PlanetCoreDrive();

    //! Maximum health of engine
    static const Health MAX_HEALTH = 100;

    /**
     * @brief canStart
     * @return False
     * @note Planet is static and doesn't travel
     * @post Exception guarantee: nothrow
     */
    bool canStart() const { return false; }

    /**
     * @brief onStart
     * @note Planet is static and doesn't travel
     * @post Exception guarantee: nothrow
     */
    void onStart();

    /**
     * @brief getValidDestinations
     * @return empty StarSystem vector
     * @note Planet is static and doesn't travel
     * @post Exception guarantee: nothrow
     */
    Common::StarSystem::StarSystemVector getValidDestinations(std::shared_ptr<Common::StarSystem> source) const;

    /**
     * @brief isValidTrip
     * @return False
     * @note Planet is static and doesn't travel
     * @post Exception guarantee: nothrow
     */
    bool isValidTrip(std::shared_ptr<Common::StarSystem> source,
                     std::shared_ptr<Common::StarSystem> destination) const;

    /**
     * @brief requiredTurns
     * @return 0
     * @note Planet is static and doesn't travel
     * @post Exception guarantee: nothrow
     */
    int requiredTurns(std::shared_ptr<Common::StarSystem> source,
                      std::shared_ptr<Common::StarSystem> destination) const;
private:
    //! Galaxy the engine is in
    std::shared_ptr<Common::IGalaxy> galaxy_;
};
}

#endif // PLANETCOREDRIVE_HH
