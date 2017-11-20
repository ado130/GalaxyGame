#ifndef UNKNOWNSTARSYSTEMEXCEPTION_HH
#define UNKNOWNSTARSYSTEMEXCEPTION_HH

#include "gameexception.hh"

class UnknownStarSystemException : public Common::GameException
{
public:
    UnknownStarSystemException(const std::string& msg = "");
};

#endif // UNKNOWNSTARSYSTEMEXCEPTION_HH
