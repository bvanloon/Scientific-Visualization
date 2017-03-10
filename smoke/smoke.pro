#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:02:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11

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
    settings/settings.cpp \
    view/colormaptab.cpp \
    colormaps/grayscalecolormap.cpp \
    colormaps/heatcolormap.cpp \
    colormaps/colormapfactory.cpp \
    view/floatslider.cpp \
    view/intslider.cpp \
    settings/canvassettings.cpp \
    settings/simulationsettings.cpp \
    settings/visualizationsettings.cpp \
    view/simulationtab.cpp \
    keyboardhandler.cpp \
    colormaps/zebramap.cpp \
    colormaps/coldcolormap.cpp \
    grid/vertex.cpp \
    grid/uniformgrid.cpp \
    grid/grid.cpp \
    grid/cell.cpp \
    grid/triangulation.cpp \
    engines/abstractengine.cpp \
    view/glyphstab.cpp \
    grid/glyphdata.cpp \
    colormaps/huecolormap.cpp \
    glyphs/glyphsfactory.cpp \
    glyphs/abstractglyph.cpp \
    glyphs/glyphstriangulation.cpp \
    glyphs/glyphtriangle.cpp
    glyphs/hedgehog.cpp \

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
    colormaps/colormapfactory.h \
    view/colormaplegend.h utilities.h \
    settings/settings.h \
    view/colormaptab.h \
    view/floatslider.h \
    view/intslider.h \
    settings/canvassettings.h \
    settings/simulationsettings.h \
    settings/visualizationsettings.h \
    view/simulationtab.h \
    keyboardhandler.h \
    colormaps/zebramap.h \
    colormaps/coldcolormap.h \
    grid/vertex.h \
    grid/uniformgrid.h \
    grid/grid.h \
    grid/cell.h \
    grid/triangulation.h \
    engines/abstractengine.h \
    view/glyphstab.h \
    grid/glyphdata.h \
    colormaps/huecolormap.h \
    glyphs/glyphsfactory.h \
    glyphs/abstractglyph.h \
    glyphs/glyphstriangulation.h \
    glyphs/glyphtriangle.h
    glyphs/hedgehog.h \

FORMS    += view/mainwindow.ui \
    view/colormaplegend.ui \
    view/colormaptab.ui \
    view/floatslider.ui \
    view/intslider.ui \
    view/simulationtab.ui \
    view/glyphstab.ui

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

DISTFILES += \
    uncrustify.cfg
