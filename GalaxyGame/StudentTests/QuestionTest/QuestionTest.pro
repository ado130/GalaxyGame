#-------------------------------------------------
#
# Project created by QtCreator 2017-11-18T18:57:19
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = questiontest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++14
TEMPLATE = app


SOURCES += questiontest.cc \
            ../../Student/question.cc \
            ../../Student/itemsingalaxy.cc \
    ../../Student/galaxy.cc \
    ../../Course/ship.cc \
    ../../Course/starsystem.cc \
    ../../Course/stateexception.cc \
    ../../Course/gameexception.cc \
    ../../Course/objectnotfoundexception.cc \
    ../../Course/formatexception.hh \
    ../../Course/ioexception.hh \
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
            ../../Student/itemsingalaxy.hh

INCLUDEPATH += $$PWD/../../Course
DEPENDPATH += $$PWD/../../Course

INCLUDEPATH += $$PWD/../../Student
DEPENDPATH += $$PWD/../../Student
