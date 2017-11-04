#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include <QGraphicsScene>

#include "starsystem.hh"
#include "starsystemui.hh"
#include "useractionhandler.hh"

typedef QList< QPair<std::shared_ptr<Common::StarSystem>, Student::StarSystemUi*> > starSystemUI_t;

namespace Ui {
class MapWindow;
}

class MapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapWindow(std::shared_ptr<Student::UserActionHandler> handler, Common::StarSystem::StarSystemVector starSystem, QWidget *parent = 0);
    ~MapWindow();

private:
    Ui::MapWindow *ui;
    std::shared_ptr<Student::UserActionHandler> handler_ = nullptr;
    QGraphicsScene *scene_ = nullptr;
    starSystemUI_t starSystemList_;

    void showStarSystems(Common::StarSystem::StarSystemVector starSystem);
public Q_SLOTS:
    void travelToStarSystem(unsigned idStarUi);
};

#endif // MAPWINDOW_H
