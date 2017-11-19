#include "unknownshipexception.hh"

UnknownShipException::UnknownShipException(const std::string &msg):
    GameException(msg)
{

}
