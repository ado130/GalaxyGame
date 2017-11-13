#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T12:45:35
#
#-------------------------------------------------

QT += core
QT += gui
QT += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GalaxyGame
TEMPLATE = app
CONFIG += c++14


SOURCES += \
    main.cc\
	mainwindow.cc \
	galaxy.cc \
	eventhandler.cc \
        statistics.cc \
    bullet.cc \
    statisticswindow.cc \
    mapwindow.cc \
    starsystemui.cc \
    useractionhandler.cc \
    starsystemscene.cc \
    planet.cc \
    planetui.cc \
    planetcoredrive.cc \
    npcshipui.cc \
    drawableobjectsmanager.cc \
    itemsingalaxy.cc \
    playershipui.cc \
    playership.cc \
    question.cc \
    questiondlg.cc

HEADERS  += \
    galaxy.hh \
    eventhandler.hh \
    statistics.hh \
	mainwindow.hh \
    bullet.hh \
    statisticswindow.hh \
    mapwindow.hh \
    starsystemui.hh \
    useractionhandler.hh \
    starsystemscene.hh \
    planet.hh \
    planetui.hh \
    planetcoredrive.hh \
    npcshipui.hh \
    drawableobjectsmanager.hh \
    itemsingalaxy.hh \
    iitemingalaxy.hh \
    itradableitem.hh \
    simpletradegoods.hh \
    playershipui.hh \
    playership.hh \
    question.hh \
    questiondlg.hh
	
FORMS += \
    mainwindow.ui \
    statisticswindow.ui \
    mapwindow.ui \
    questiondlg.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += $$PWD/../Course
DEPENDPATH += $$PWD/../Course

CONFIG(release, debug|release) {
   DESTDIR = release
}

CONFIG(debug, debug|release) {
   DESTDIR = debug
}

win32 {
 #   copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) for Windows &
    copyfiles.commands += xcopy ..\\..\\GalaxyGame\\Assets Assets /i /s /e /y
}
unix:!macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for Linux\" &&
    copyfiles.commands += cp -r ../../GalaxyGame/Assets $$DESTDIR
}
macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for MacOS\" &&
    copyfiles.commands += mkdir -p $$DESTDIR/GalaxyGame.app/Contents/MacOS &&
    copyfiles.commands += cp -r ../../GalaxyGame/Assets $$DESTDIR &&
    copyfiles.commands += cp -r ../../GalaxyGame/Assets $$DESTDIR/GalaxyGame.app/Contents/MacOS/
}

LIBS += -L$$OUT_PWD/../Course/
LIBS += -L$$OUT_PWD/../Course/$${DESTDIR}/ -lCourse


QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
