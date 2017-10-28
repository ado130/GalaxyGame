#include "eventhandler.hh"

#include <QDebug>

Student::EventHandler::EventHandler()
{

}

Student::EventHandler::~EventHandler()
{

}

void Student::EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship)
{
}

void Student::EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship)
{
    qDebug() << "shipRemoved";
}

void Student::EventHandler::shipRelocated(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem)
{
    qDebug() << "shipRelocated";
}

void Student::EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship, Common::Point origin, Common::Point target)
{
    qDebug() << "shipMoved";
}

void Student::EventHandler::exceptionInExecution(std::shared_ptr<Common::Ship> ship, const std::string &msg)
{
    qDebug() << "exceptionInExecution";
}

void Student::EventHandler::distressOn(std::shared_ptr<Common::Ship> ship)
{
    qDebug() << "distressOn";
}

void Student::EventHandler::distressOff(std::shared_ptr<Common::Ship> ship)
{
    qDebug() << "distressOff";
}

void Student::EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    qDebug() << "shipAbandoned";
}
