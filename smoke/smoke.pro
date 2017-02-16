#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:02:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


macx {
    QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.10
}


TARGET = smoke
TEMPLATE = app


SOURCES += main.cpp\
        view/mainwindow.cpp \
    view/canvas.cpp \
    engines/triangleengine.cpp \
    simulation/simulation.cpp \
    simulation/simulationrealization.cpp \
    settings/settings.cpp \
    simulation/utils.cpp \
    engines/vectorengine.cpp \
    engines/smokeengine.cpp
    colormaps/abstractcolormap.cpp \
    colormaps/rainbowcolormap.cpp
    engines/smokeengine.cpp \
    view/colormaplegend.cpp

HEADERS  += main.ih\
        view/mainwindow.h \
    view/canvas.h \
    engines/triangleengine.h \
    simulation/simulation.h \
    simulation/simulationrealization.h \
    settings/settings.h \
    simulation/utils.h \
    engines/vectorengine.h \
    engines/smokeengine.h
    colormaps/abstractcolormap.h \
    colormaps/rainbowcolormap.h
    engines/smokeengine.h \
    view/colormaplegend.h

FORMS    += view/mainwindow.ui \
    view/colormaplegend.ui

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
