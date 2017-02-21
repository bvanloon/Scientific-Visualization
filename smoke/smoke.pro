#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:02:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

macx {
    QMAKE_CXXFLAGS += -stdlib=libc++ -mmacosx-version-min=10.10
}


TARGET = smoke
TEMPLATE = app


SOURCES += main.cpp\
        view/mainwindow.cpp \
    view/canvas.cpp \
    simulation/simulation.cpp \
    colormaps/abstractcolormap.cpp \
    colormaps/rainbowcolormap.cpp \
    simulation/simulationrealization.cpp \
    simulation/utils.cpp \
    engines/vectorengine.cpp \
    engines/smokeengine.cpp \
    view/colormaplegend.cpp utilities.cpp \
    view/simulationsettingpane.cpp \
    settings/simulations.cpp \
    settings/canvass.cpp \
    settings/visualizations.cpp \
    settings/settings.cpp \
    view/visualizationsettingpane.cpp

HEADERS  += main.ih\
        view/mainwindow.h \
    view/canvas.h \
    simulation/simulation.h \
    simulation/simulationrealization.h \
    simulation/utils.h \
    engines/vectorengine.h \
    engines/smokeengine.h \
    colormaps/abstractcolormap.h \
    colormaps/rainbowcolormap.h \
    view/colormaplegend.h utilities.h \
    view/simulationsettingpane.h \
    settings/simulations.h \
    settings/canvass.h \
    settings/visualizations.h \
    settings/settings.h \
    view/visualizationsettingpane.h

FORMS    += view/mainwindow.ui \
    view/colormaplegend.ui \
    view/simulationsettingpane.ui \
    view/visualizationsettingspane.ui

RESOURCES += \
    shaders.qrc

unix: LIBS += -L$$PWD/fftw-2.1.5/lib/ -lrfftw

INCLUDEPATH += $$PWD/fftw-2.1.5/include
DEPENDPATH += $$PWD/fftw-2.1.5/include

unix: PRE_TARGETDEPS += $$PWD/fftw-2.1.5/lib/librfftw.a

unix: LIBS += -L$$PWD/fftw-2.1.5/lib/ -lfftw

INCLUDEPATH += $$PWD/fftw-2.1.5/include
DEPENDPATH += $$PWD/fftw-2.1.5/include

unix: PRE_TARGETDEPS += $$PWD/fftw-2.1.5/lib/libfftw.a
