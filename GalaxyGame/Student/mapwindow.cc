#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include <QDebug>

MapWindow::MapWindow(std::shared_ptr<Student::UserActionHandler> handler, Common::StarSystem::StarSystemVector starSystem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapWindow), handler_(handler)
{
    ui->setupUi(this);

    QObject* eventHandlerObj = dynamic_cast<QObject*>(handler_.get());
    connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)), this, SLOT(travelToStarSystem(unsigned)));

    showStarSystems(starSystem);
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::showStarSystems(Common::StarSystem::StarSystemVector starSystem)
{
    for(Common::StarSystem::StarSystemVector::size_type i = 0; i < starSystem.size(); ++i)
    {
        if(scene_ == nullptr)
        {
            scene_ = new QGraphicsScene(this);
            scene_->clear();
            scene_->setBackgroundBrush( Qt::lightGray );
            ui->graphicsView->setScene(scene_);
        }

        Student::StarSystemUi *starSystemUi = new Student::StarSystemUi(handler_, starSystem.at(i).get()->getCoordinates(), starSystem.at(i).get()->getId());
        scene_->addItem(starSystemUi);
        starSystemList_.append(qMakePair(starSystem.at(i), starSystemUi));
    }
}

void MapWindow::travelToStarSystem(unsigned idStarUi)
{
    // ToDo: Mark current system on map
//    qDebug() << "MAP " << idStarUi;
}
