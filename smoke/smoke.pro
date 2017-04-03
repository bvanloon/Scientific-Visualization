#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T20:02:50
#
#-------------------------------------------------

QT       += core gui

CONFIG += object_parallel_to_source
OBJECTS_DIR = ../build/

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
    engines/smokeengine.cpp \
    view/colormaplegend.cpp \
    settings/settings.cpp \
    view/colormaptab.cpp \
    colormaps/grayscalecolormap.cpp \
    colormaps/heatcolormap.cpp \
    colormaps/colormapfactory.cpp \
    view/floatslider.cpp \
    view/intslider.cpp \
    settings/canvassettings.cpp \
    settings/simulationsettings.cpp \
    settings/visualization/visualizationsettings.cpp \
    settings/visualization/smokesettings.cpp \
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
    colormaps/huecolormap.cpp \
    glyphs/abstractglyph.cpp \
    glyphs/hedgehog.cpp \
    glyphs/triangle.cpp \
    glyphs/ccwtriangle.cpp \
    glyphs/airplane.cpp \
    utilities/range.cpp \
    utilities/mesh.cpp \
    utilities/vector.cpp \
    utilities/approximation.cpp \
    settings/visualization/streamlines.cpp \
    view/streamlinestab.cpp \
    engines/seedpointengine.cpp \
    shapes/rectangle.cpp \
    glyphs/cone.cpp \
    shapes/cone.cpp \
    engines/streamlineengine.cpp \
    shapes/polyline.cpp \
    utilities/gpudata.cpp \
    streamobjects/streamline.cpp \
    grid/utilities/streamlinebuilder.cpp \
    grid/jittergrid.cpp \
    engines/smokeslicesengine.cpp \
    engines/glyphsliceengine.cpp \
    engines/streamlineslicesengine.cpp \
    engines/abstractsliceengine.cpp \
    utilities/rotation.cpp \
    settings/visualization/slices.cpp \
    view/slicestab.cpp \
    simulation/simulationdata.cpp \
    grid/simulationgrid.cpp \
    simulation/simulationstatehistory.cpp \
    grid/utilities/smokebuilder.cpp \
    engines/glyphengine.cpp \
    grid/utilities/glyphbuilder.cpp \
    settings/visualization/glyphs.cpp

HEADERS  += main.ih\
        colormaps/abstractcolormap.h \
    colormaps/coldcolormap.h \
    colormaps/colormapfactory.h \
    colormaps/huecolormap.h \
    colormaps/rainbowcolormap.h \
    colormaps/zebramap.h \
    engines/abstractengine.h \
    engines/abstractsliceengine.h \
    engines/glyphengine.h \
    engines/glyphsliceengine.h \
    engines/seedpointengine.h \
    engines/smokeengine.h \
    engines/smokeslicesengine.h \
    engines/streamlineengine.h \
    engines/streamlineslicesengine.h \
    glyphs/abstractglyph.h \
    glyphs/airplane.h \
    glyphs/ccwtriangle.h \
    glyphs/cone.h \
    glyphs/glyphs.h \
    glyphs/hedgehog.h \
    glyphs/triangle.h \
    grid/cell.h \
    grid/grid.h \
    grid/jittergrid.h \
    grid/simulationgrid.h \
    grid/triangulation.h \
    grid/uniformgrid.h \
    grid/utilities/glyphbuilder.h \
    grid/utilities/smokebuilder.h \
    grid/utilities/streamlinebuilder.h \
    grid/vertex.h \
    keyboardhandler.h \
    settings/canvassettings.h \
    settings/settings.h \
    settings/simulationsettings.h \
    settings/visualization/glyphs.h \
    settings/visualization/slices.h \
    settings/visualization/streamlines.h \
    settings/visualizationsettings.h \
    shapes/cone.h \
    shapes/polyline.h \
    shapes/rectangle.h \
    simulation/simulation.h \
    simulation/simulationdata.h \
    simulation/simulationrealization.h \
    simulation/simulationstatehistory.h \
    simulation/utils.h \
    streamobjects/streamline.h \
    unused.h \
    utilities/approximation.h \
    utilities/gpudata.h \
    utilities/mesh.h \
    utilities/range.h \
    utilities/rotation.h \
    utilities/sizelimitedqueue.h \
    utilities/vector.h \
    view/canvas.h \
    view/colormaplegend.h \
    view/colormaptab.h \
    view/floatslider.h \
    view/glyphstab.h \
    view/intslider.h \
    view/mainwindow.h \
    view/simulationtab.h \
    view/slicestab.h \
    view/streamlinestab.h

FORMS    += view/mainwindow.ui \
    view/colormaplegend.ui \
    view/colormaptab.ui \
    view/floatslider.ui \
    view/intslider.ui \
    view/simulationtab.ui \
    view/glyphstab.ui \
    view/streamlinestab.ui \
    view/slicestab.ui

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
