#ifndef UNKNOWNSHIPEXCEPTION_HH
#define UNKNOWNSHIPEXCEPTION_HH

#include "gameexception.hh"

class UnknownShipException : public Common::GameException
{
public:
    UnknownShipException(const std::string& msg = "");
    ~UnknownShipException() {}
};

#endif // UNKNOWNSHIPEXCEPTION_HH
