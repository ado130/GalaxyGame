#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <memory>

#include "starsystem.hh"
#include "starsystemui.hh"
#include "useractionhandler.hh"
#include "igalaxy.hh"

typedef QList< QPair<std::shared_ptr<Common::StarSystem>, Student::StarSystemUi*> > starSystemUI_t;

namespace Ui {
class MapWindow;
}

class MapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapWindow(std::shared_ptr<Student::UserActionHandler> handler,
                       Common::StarSystem::StarSystemVector starSystem,
                       std::shared_ptr<Common::StarSystem> currentStarSystem,
                       QWidget *parent = 0);
    ~MapWindow();

    void setPlanetsByStarSystem(Common::IGalaxy::ShipVector planets) {planets_ = planets;}
    void markStarSystemAsDistressed(std::shared_ptr<Common::StarSystem> starSystem);
    void unmarkStarSystemDistress(std::shared_ptr<Common::StarSystem> starSystem);
    void addMarkSign(QGraphicsPixmapItem *starSystemUi, QPixmap pixmap, int x, int y);
private:
    Ui::MapWindow *ui;
    std::shared_ptr<Student::UserActionHandler> handler_ = nullptr;
    QGraphicsScene *scene_ = nullptr;
    starSystemUI_t starSystemList_;
    Common::IGalaxy::ShipVector planets_;
    int coordsScale_ = 30;
    std::vector<QGraphicsPixmapItem*> distressedStarSystemItems_;
    QGraphicsPixmapItem* playerLocation_ = nullptr;
    QPixmap pixDistressed_;
    QPixmap pixAbandoned_;

    void showStarSystems(Common::StarSystem::StarSystemVector starSystem);
public Q_SLOTS:
    void travelToStarSystem(unsigned idStarUi);
    void showGoodsInfo(unsigned idStarUi);

Q_SIGNALS:
    void planetsByStarSystemRequest(unsigned id);
};

#endif // MAPWINDOW_H
