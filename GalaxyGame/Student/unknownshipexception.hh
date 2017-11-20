#ifndef UNKNOWNSHIPEXCEPTION_HH
#define UNKNOWNSHIPEXCEPTION_HH

#include "gameexception.hh"

/**
 * @brief The UnknownShipException is thrown when certain Ship cannot be found
 * or recognized
 */
class UnknownShipException : public Common::GameException
{
public:
    /**
     * @brief UnknownShipException
     * @param msg description of exception
     */
    UnknownShipException(const std::string& msg = "");

    /**
     * @brief Destructor
     */
    ~UnknownShipException() {}
};

#endif // UNKNOWNSHIPEXCEPTION_HH
