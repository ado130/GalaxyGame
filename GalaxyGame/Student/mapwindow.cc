#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "planet.hh"

#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

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

void MapWindow::showGoodsInfo(unsigned idStarUi)
{
    std::shared_ptr<Common::StarSystem> starSystem = nullptr;
    for(auto k : starSystemList_)
    {
        if(k.first->getId() == idStarUi)
        {
            starSystem = k.first;
        }
    }

    if(starSystem != nullptr)
    {
        ui->ptPlanets->clear();

        const char* economy[] = { "Refinery", "Extraction", "HiTech", "Industrial", "Tourism", "Agriculture", "Service", "Military", "Terraforming", "Colony", "None" };
        QString text = "Name: " + QString(starSystem->getName().data()) + "\n";
        text += "Economy: " + QString(economy[starSystem->getEconomy()]) + "\n";
        text += "--------------------------------------";
        ui->ptPlanets->appendPlainText(text);

        emit planetsByStarSystemRequest(starSystem->getId());

        if(planets_.empty())
        {
            ui->ptPlanets->appendPlainText("Star system does not contain any planets!");
        }
        else
        {
            for(auto k : planets_)
            {
                Student::Planet* planet = static_cast<Student::Planet*>(k.get());
                QString info = "Name: " + QString(planet->getName().data());
                info += "Goods: " + QString(planet->getGoods().getName().data()) + "\n";
                info += "Price: " + QString::number(planet->getGoods().getPrice()) + "\n";
                ui->ptPlanets->appendPlainText(info);
            }
        }
    }
}
