#ifdef Finnish_dox
/**
* @file ieventhandler.hh
* @brief Määrittelee tapahtumankäsittelijän rajapinnan
*/

/**
* @namespace Common
*/

/**
* @class Common::IEventHandler
* @brief Tapahtumanvälittäjä ottaa vastaan tapahtumia ja delegoi niiden käsittelyn eteenpäin.
*
* Tapahtumankäsittelijää välitetään parametrinä kaikille niille olioille, joiden tarvitsee ilmoittaa
* tapahtumista. Tällaisia ovat esimerkiksi alukset ja jotkin actionit
*
* Näitä tapahtumia voi käyttää apuna käyttöliittymän päivittämiseen.
*
*/

/**
* Tarpeellisten luokkien ennakkoesittelyt.
*/
class Ship;
class StarSystem;
struct Point;


/**
* @fn Common::IEventHandler::IEventHandler() = default;
* @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten)
*/


/**
* @fn virtual Common::IEventHandler::~IEventHandler() = default;
* @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
*/


/**
* @fn virtual void Common::IEventHandler::shipSpawned(std::shared_ptr<Ship> ship) = 0;
* @brief shipSpawned Uusi alus on luotu galaksiin.
* @param ship luotu alus
*/


/**
* @fn virtual void Common::IEventHandler::shipRemoved (std::shared_ptr<Ship> ship) = 0 ;
* @brief shipRemoved Alus poistettu galaksista.
* @param ship poistettu alus
*/


/**
* @fn virtual void Common::IEventHandler::shipMoved(std::shared_ptr<Ship> ship, Point origin, Point target) = 0 ;
* @brief shipMoved  Alus on siirtynyt pisteestä toiseen
* @param ship liikkunut alus
* @param origin piste, josta alus lähti liikkeelle
* @param target piste, jonne alus saapui
*/


/**
* @fn virtual void Common::IEventHandler::shipRelocated(std::shared_ptr<Ship> ship, std::shared_ptr<StarSystem> starSystem) = 0;
* @brief shipRelocated Alus on siirtynyt annettuun tähtijärjestelmään.
* @param ship, alus joka vaihdoi sijaintia
* @param starSystem nullptr, kun alus poistuu järjestelmästä, järjestelmä johon saavuttiin, jos alus saapui perille
*/


/**
* @fn virtual void Common::IEventHandler::exceptionInExecution(std::shared_ptr<Ship>, std::string const&) = 0;
* @brief exceptionInExecution Aluksen suorittama toiminto on aiheuttanut poikkeuksen, jolla oli annettu merkkijono selitteenä.
*/


/**
* @fn  virtual void Common::IEventHandler::distressOn(std::shared_ptr<Ship> ship) = 0 ;
* @brief distressOn Alus on tehnyt hätäkutsun.
* @param ship hätäkutsun tehnyt alus
*/



/**
* @fn virtual void Common::IEventHandler::distressOff(std::shared_ptr<Ship> ship) = 0;
* @brief distressOff Alus on sulkenut hätäkutsun.
* @param ship hätäkutsun sulkenut alus
*/

/**
* @fn virtual void Common::IEventHandler::shipAbandoned(std::shared_ptr<Ship> ship) = 0;
* @brief shipAbandoned Alus on hylätty.
* @param ship hylätty alus
*/

#endif // IEVENTHANDLER_HH
