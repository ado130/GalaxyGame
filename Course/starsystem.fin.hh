#ifdef Finnish_dox

/**
 * @file starsystem.hh
 * @brief Tähtijärjestelmä, sijainnin perusyksikkö.
 */

/**
  @namespace Common
*/

/**
 * @class Common::StarSystem
 * @brief Galaksit koostuvat tähtijärjestelmistä.
 *
 * Tähtijärjestelmä on dataluokka, joka koostuu kentistä kuten koordinaatit, väkiluku ja elinkeino.
 * Moni muu asia pelilogiikassa, kuten alusten siirtyminen ja rahti, ovat tähtijärjestelmien varassa.
 */

/**
 * @brief Vektorityyppi, joka pitää sisällään osoittimia tähtijärjestelmiin.
 *
 * @typedef std::vector<std::shared_ptr<StarSystem> > Common::StarSystem::Vector;
 */

/**
 * @var static const int Common::StarSystem::POPULATION_REPAIR_TRESHOLD;
 * @brief Jos väkiluku ylittää tämän kynnysarvon, voidaan tähtijärjestelmässä korjata ilman huoltoa.
 */

/**
 * @enum Common::StarSystem::ECONOMY_TYPE
 * @brief Tietotyyppi, jolla ilmaistaan tähtijärjestelmän pääasiallinen elinkeino.
 */

/**
 * @fn Common::StarSystem::StarSystem();
 * @brief Rakentaja.
 * @param name Tähtijärjestelmän nimi.
 * @param economy Tähtijärjestelmän pääasiallinen elinkeino.
 * @param id Tähtijärjestelmän tunniste.
 * @param population Tähtijärjestelmän väkiluku.
 * @param location Tähtijärjestelmän sijainti koordinaateissa.
 */

/**
 * @fn std::string Common::StarSystem::getName() const;
 * @return Tähtijärjestelmän nimi.
 */

/**
 * @fn Common::StarSystem::ECONOMY_TYPE Common::StarSystem::getEconomy();
 * @return Tähtijärjestelmän pääasiallinen elinkeino.
 */

/**
 * @fn unsigned Common::StarSystem::getId() const;
 * @return Tähtijärjestelmän tunniste.
 */

/**
 * @fn uint64_t getPopulation() const;
 * @return Tähtijärjestelmän väkiluku.
 */

/**
 * @fn Common::Point Common::StarSystem::getCoordinates() const;
 * @return Tähtijärjestelmän sijainti koordinaateissa.
 */

/**
 * @fn bool Common::StarSystem::isInhabited() const;
 * @brief Onko tähtijärjestelmä asutettu.
 * @return Tosi, jos on, muutoin epätosi.
 */

/**
 * @fn bool Common::StarSystem::canRepair() const;
 * @brief Voiko tähtijärjestelmässä suorittaa korjauksia ilman lisävarusteita.
 * @return Tosi, jos voi, muutoin epätosi.
 */

/**
  * @private
*/
//! Tähtijärjestelmän nimi.
//! @variable std::string name_;
//! Tähtijärjestelmän pääasiallinen elinkeino.
//! @variable ECONOMY_TYPE economy_;
//! Tähtijärjestelmän tunniste.
//! @variable unsigned id_;
//! Tähtijärjestelmän väkiluku.
//! @variable uint64_t population_;
//! Tähtijärjestelmän sijainti koordinaateissa.
//! @variable Point coordinates_;

// EOF: starsystem.fin.hh
#endif
