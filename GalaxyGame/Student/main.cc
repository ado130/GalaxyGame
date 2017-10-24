#include "mainwindow.hh"
#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"

#include <memory>
#include <QApplication>
#include <time.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Semicolon - Space game");

    std::shared_ptr<Common::IEventHandler> handler = std::make_shared<Student::EventHandler>();
    std::shared_ptr<Student::Galaxy> galaxy = std::make_shared<Student::Galaxy>();
    std::shared_ptr<Common::IGameRunner> gameRunner = Common::getGameRunner(galaxy, handler);
    Common::utilityInit(time(NULL));

    MainWindow w(0, handler, galaxy, gameRunner);
    w.show();

    return a.exec();
}
