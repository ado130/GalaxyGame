#ifdef Finnish_dox

/**
*@file istatistics.hh
* @brief Määrittelee luokan, joka pitää kirjaa pelin tilasta
*/

/**
* @class Common::IStatistics
* @brief Määrittelee rajapinnan konkreettiselle tilastoluokalle
*
*
* @invariant getCreditBalance() > MAX_LOAN_ALLOWANCE && getPoints() > 0
*/


/**
* @fn Common::IStatistics::IStatistics() = default;
* @brief Rajapintaluokan oletusrakentaja (olemassa dokumentaatiota varten).
* @post Alkuarvot on asetettu valinnan mukaiseksi.
*/


/**
* @fn virtual Common::IStatistics::~IStatistics() = default;
* @brief Rajapintaluokassa on oletusarvoinen virtuaalipurkaja (olemassa, koska kantaluokalla tulee olla virtuaalipurkaja).
*/


/**
* @fn virtual void Common::IStatistics::addSavedShip() = 0;
* @brief addSavedShip lisää yhden kiipelistä pelastetun aluksen
*
*/

/**
* @fn virtual unsigned Common::IStatistics::getSavedShips() const = 0;
* @brief getSavedShips kertoo pelastetun alusten määrän
*/

/**
* @fn virtual void Common::IStatistics::addLostShip() = 0;
* @brief addLostShip lisää yhden menetetyn (galaksista poistuneen) aluksen
*/


/**
* @fn virtual unsigned Common::IStatistics::getLostShips() const = 0;
* @brief getLostShips kertoo menetettyjen alusten määrän.
*/


/**
* @fn virtual void Common::IStatistics::addPoints(unsigned amount) = 0;
* @brief addPoints lisää pelaajalle pisteitä annetun määrän
* @param amount Lisättävien pisteiden määrä
*/


/**
* @fn virtual void Common::IStatistics::reducePoints(unsigned amount) = 0;
* @brief reducePoints vähentää pelaajan pisteitä
* @param amount Vähennettävien pisteiden määrä
* @exception StateException, jos invariantti rikkoutuu
*/


/**
* @fn virtual unsigned Common::IStatistics::getPoints() const = 0;
* @brief getPoints kertoo pelaajien pisteiden kokonaismäärän
*/


/**
* @fn virtual void Common::IStatistics::addCredits(unsigned amount) = 0;
* @brief addCredits lisää pelaajan "tilille" crediittejä
* @param amount Lisättävien crediittien määrä
*/


/**
* @fn virtual void Common::IStatistics::reduceCredits(unsigned amount) = 0;
* @brief reduceCredits vähentää pelaajan "tililtä" crediittejä
* @param amount Vähennettävien crediittien määrä
* @exception StateException, jos invariantti rikkoutuu
*/


/**
* @fn virtual int Common::IStatistics::getCreditBalance() const = 0;
* @brief getCreditBalance palauttaa jäljellä olevien crediittien määrän
*/


#endif

// EOF: istatistics.fin.hh
