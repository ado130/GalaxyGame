#include "useractionhandler.hh"

Student::UserActionHandler::UserActionHandler(QObject* parent) : QObject(parent)
{

}


Student::UserActionHandler::~UserActionHandler()
{

}

void Student::UserActionHandler::travelToStarSystemRequest(unsigned idStarUi)
{
    emit travelRequest(idStarUi);
}
