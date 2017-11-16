#include "eventhandler.hh"

#include <QDebug>

Student::EventHandler::EventHandler(QObject *parent) : QObject(parent)
{
}

Student::EventHandler::~EventHandler()
{
}

void Student::EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship)
{
    //This signal invokes drawableObjManager, but nothing is drawed yet.
    //It creates UI reprezentation of this ship and pairs them in drawableObjManager
    emit registerShipToUi(ship);
}

void Student::EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship)
{
    emit unregisterShipFromUi(ship);
}

void Student::EventHandler::shipRelocated(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem)
{
    if(ship != nullptr || starSystem != nullptr)
    {
        emit shipChangedLocation(ship, starSystem);
    }
}

void Student::EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship, Common::Point origin, Common::Point target)
{
    emit shipMovement(ship, origin, target);
}

void Student::EventHandler::exceptionInExecution(std::shared_ptr<Common::Ship> ship, const std::string &msg)
{

}

void Student::EventHandler::distressOn(std::shared_ptr<Common::Ship> ship)
{
    emit shipCallForHelp(ship);
}

void Student::EventHandler::distressOff(std::shared_ptr<Common::Ship> ship)
{
    emit shipWasSaved(ship);
}

void Student::EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    emit shipWasAbandoned(ship);
}
