#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T20:53:47
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = questiontest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++14
TEMPLATE = app


SOURCES += questiontesttest.cpp \
           ../../Student/question.cc \
           ../../Student/galaxy.cc \
           ../../Student/planet.cc \
           ../../Student/itemsingalaxy.cc \
           ../../Student/eventhandler.cc \
           ../../Student/planetcoredrive.cc \
    ../../Course/ship.cc \
    ../../Course/starsystem.cc \
    ../../Course/stateexception.cc \
    ../../Course/gameexception.cc \
    ../../Course/ioexception.cc \
    ../../Course/formatexception.cc \
    ../../Course/objectnotfoundexception.cc \
    ../../Course/utility.cc \
    ../../Course/warpdrive.cc \
    ../../Course/shipengine.cc \
    ../../Course/cargoship.cc \
    ../../Course/repairaction.cc \
    ../../Course/distressaction.cc \
    ../../Course/loadcargo.cc \
    ../../Course/unloadcargo.cc \
    ../../Course/chargeaction.cc \
    ../../Course/wormholedrive.cc \
    ../../Course/moveaction.cc



DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS +=  ../../Student/question.hh \
            ../../Student/galaxy.hh \
            ../../Student/planet.hh \
            ../../Student/itemsingalaxy.hh \
            ../../Student/eventhandler.hh \
            ../../Student/planetcoredrive.hh

INCLUDEPATH += ../../Student ../../Course/
DEPENDPATH += ../../Student


win32 {
 #   copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) for Windows &
    copyfiles.commands += xcopy ..\\..\\..\\GalaxyGame\\Assets Assets /i /s /e /y
}
unix:!macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for Linux\" &&
    copyfiles.commands += cp -r ../../../GalaxyGame/Assets Assets
}
macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for MacOS\" &&
    copyfiles.commands += mkdir -p $$DESTDIR/GalaxyGame.app/Contents/MacOS &&
    copyfiles.commands += cp -r ../../../GalaxyGame/Assets $$DESTDIR &&
    copyfiles.commands += cp -r ../../../GalaxyGame/Assets $$DESTDIR/GalaxyGame.app/Contents/MacOS/
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
