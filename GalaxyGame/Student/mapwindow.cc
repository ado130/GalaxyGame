#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "planet.hh"
#include "unknownstarsystemexception.hh"

#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <cassert>

MapWindow::MapWindow(std::shared_ptr<Student::UserActionHandler> handler,
                     Common::StarSystem::StarSystemVector starSystem,
                     std::shared_ptr<Common::StarSystem> currentStarSystem,
                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapWindow), handler_(handler)
{
    ui->setupUi(this);

    QObject* eventHandlerObj = dynamic_cast<QObject*>(handler_.get());
    connect(eventHandlerObj, SIGNAL(travelRequest(unsigned)), this, SLOT(travelToStarSystem(unsigned)));

    pixDistressed_ = QPixmap(":/images/images/distressed.png");
    pixQuestion_ = QPixmap(":/images/images/question.png");
    QPixmap playerLocationPixmap = QPixmap(":/images/images/location-pointer.png");
    playerLocationPixmap = playerLocationPixmap.scaledToWidth(playerLocationPixmap.width()/2);

    showStarSystems(starSystem);

    playerLocation_ = new QGraphicsPixmapItem();
    playerLocation_->setPixmap(playerLocationPixmap);
    playerLocation_->setPos(currentStarSystem->getCoordinates().x*coordsScale_,
                            currentStarSystem->getCoordinates().y*coordsScale_-starSystemList_[0].second->boundingRect().height()/2);
    scene_->addItem(playerLocation_);

}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::markStarSystemAsDistressed(std::shared_ptr<Common::StarSystem> starSystem)
{
    assert(!pixDistressed_.isNull());

    for(auto element : starSystemList_)
    {
        if(element.first == starSystem)
        {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
            distressedStarSystemItems_.push_back(item);
            addMarkSign(item, pixDistressed_, element.second->x()+element.second->boundingRect().right(), element.second->y());
            return;
        }
    }
    throw Student::UnknownStarSystemException("Star System " + starSystem->getName() + " was not found.");
}

void MapWindow::unmarkStarSystemDistress(std::shared_ptr<Common::StarSystem> starSystem)
{
    assert(scene_);

    for(auto item : distressedStarSystemItems_)
    {
        for(auto element : starSystemList_)
        {
            if(element.first == starSystem)
            {
                if(cmpf(item->x(), element.second->x()+element.second->boundingRect().right()) &&
                        cmpf(item->y(), element.second->y()))
                {
                    scene_->removeItem(item);
                    return;
                }
            }
        }
    }
    throw Student::UnknownStarSystemException("Star System " + starSystem->getName() + " was not found.");
}

void MapWindow::markQuestionStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    assert(!pixQuestion_.isNull());

    for(auto element : starSystemList_)
    {
        if(element.first == starSystem)
        {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
            addMarkSign(item, pixQuestion_, element.second->x()+element.second->boundingRect().right(), element.second->y());
            return;
        }
    }
    throw Student::UnknownStarSystemException("Star System " + starSystem->getName() + " was not found.");
}

void MapWindow::addMarkSign(QGraphicsPixmapItem *item, QPixmap pixmap, int x, int y)
{
    assert(scene_);

    if(item != nullptr)
    {
        item->setPixmap(pixmap);
        item->setPos(x, y);
        scene_->addItem(item);
    }
}

void MapWindow::showStarSystems(Common::StarSystem::StarSystemVector starSystem)
{
    assert(handler_);
    assert(ui);

    QPixmap pix = QPixmap(":/images/images/deathStar.png");
    QPixmap smallerPix = pix.scaledToWidth(pix.width()/4);

    for(Common::StarSystem::StarSystemVector::size_type i = 0; i < starSystem.size(); ++i)
    {
        if(scene_ == nullptr)
        {
            scene_ = new QGraphicsScene(this);
            scene_->clear();
            scene_->setBackgroundBrush( Qt::lightGray );
            ui->graphicsView->setScene(scene_);
        }

        Common::Point mapCoords = Common::Point(starSystem.at(i).get()->getCoordinates().x*coordsScale_,
                                  starSystem.at(i).get()->getCoordinates().y*coordsScale_);
        Ui::StarSystemUi *starSystemUi = new Ui::StarSystemUi(smallerPix, handler_,
                                                                        mapCoords,
                                                                        starSystem.at(i).get()->getId());
        scene_->addItem(starSystemUi);
        starSystemList_.append(qMakePair(starSystem.at(i), starSystemUi));
    }
}

bool MapWindow::cmpf(double A, double B, double epsilon)
{
    return (fabs(A - B) < epsilon);
}

void MapWindow::travelToStarSystem(unsigned idStarUi)
{
    assert(playerLocation_);

    for(auto k : starSystemList_)
    {
        if(k.first->getId() == idStarUi)
        {
            playerLocation_->setPos(k.second->x(), k.second->y()-k.second->boundingRect().height()/2);
            return;
        }
    }
    throw Student::UnknownStarSystemException("Star System with id " + std::to_string(idStarUi) + " was not found.");
}

void MapWindow::showGoodsInfo(unsigned idStarUi)
{
    assert(ui);

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
        QString text = "----------------------------------\n";
        text += "Star system name: " + QString(starSystem->getName().data()) + "\n";
        text += "Economy: " + QString(economy[starSystem->getEconomy()]) + "\n";
        text += "----------------------------------";
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
                QString info = "Name: " + QString(planet->getName().data()) + "\n";
                info += "Goods: " + QString(planet->getGoods().getName().data()) + "\n";
                info += "Price: " + QString::number(planet->getGoods().getPrice()) + "\n";
                ui->ptPlanets->appendPlainText(info);
            }
        }
    }
}
