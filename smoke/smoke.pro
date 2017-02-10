#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:02:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smoke
TEMPLATE = app


SOURCES += main.cpp\
        view/mainwindow.cpp \
    view/canvas.cpp \
    engines/triangleengine.cpp \
    simulation/simulation.cpp

HEADERS  += main.ih\
        view/mainwindow.h \
    view/canvas.h \
    engines/triangleengine.h \
    simulation/simulation.h

FORMS    += view/mainwindow.ui

RESOURCES += \
    shaders.qrc
