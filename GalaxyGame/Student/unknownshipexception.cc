#include "unknownshipexception.hh"

Student::UnknownShipException::UnknownShipException(const std::string &msg):
    GameException(msg)
{

}
