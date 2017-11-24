#include "mainwindow.hh"
#include "galaxy.hh"
#include "initialize.hh"
#include "igamerunner.hh"
#include "utility.hh"
#include "eventhandler.hh"

#include <memory>
#include <QApplication>
#include <QMessageBox>
#include <time.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Semicolon - Space game");

    std::shared_ptr<Common::IEventHandler> handler;
    std::shared_ptr<Student::Galaxy> galaxy;
    std::shared_ptr<Common::IGameRunner> gameRunner;
    try
    {
        handler = std::make_shared<Student::EventHandler>();
        galaxy = std::make_shared<Student::Galaxy>();
        gameRunner = Common::getGameRunner(galaxy, handler);
        Common::utilityInit(time(NULL));
    }
    catch (...)
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/images/images/favicon.png"));
        msgBox.setText("Error occured! Program has to be terminated. Reason: problem with loading game files");
        msgBox.exec();

        exit(1);
    }

    MainWindow w(0, handler, galaxy, gameRunner);
    w.show();
    return a.exec();
}
