#ifndef UNKNOWNSTARSYSTEMEXCEPTION_HH
#define UNKNOWNSTARSYSTEMEXCEPTION_HH

#include "gameexception.hh"

/**
 * @brief The UnknownStarSystemException is thrown when certain StarSystem cannot be found
 * or recognized
 */
class UnknownStarSystemException : public Common::GameException
{
public:
    /**
     * @brief UnknownShipException
     * @param msg description of exception
     */
    UnknownStarSystemException(const std::string& msg = "");

    /**
     * @brief Destructor
     */
    ~UnknownStarSystemException(){}
};

#endif // UNKNOWNSTARSYSTEMEXCEPTION_HH
