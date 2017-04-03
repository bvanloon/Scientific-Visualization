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
        colormaps/abstractcolormap.cpp \
    colormaps/coldcolormap.cpp \
    colormaps/colormapfactory.cpp \
    colormaps/grayscalecolormap.cpp \
    colormaps/heatcolormap.cpp \
    colormaps/huecolormap.cpp \
    colormaps/rainbowcolormap.cpp \
    colormaps/zebramap.cpp \
    engines/abstractengine.cpp \
    engines/abstractsliceengine.cpp \
    engines/glyphengine.cpp \
    engines/glyphsliceengine.cpp \
    engines/seedpointengine.cpp \
    engines/smokeengine.cpp \
    engines/smokeslicesengine.cpp \
    engines/streamlineengine.cpp \
    engines/streamlineslicesengine.cpp \
    glyphs/abstractglyph.cpp \
    glyphs/airplane.cpp \
    glyphs/ccwtriangle.cpp \
    glyphs/cone.cpp \
    glyphs/hedgehog.cpp \
    glyphs/triangle.cpp \
    grid/cell.cpp \
    grid/grid.cpp \
    grid/jittergrid.cpp \
    grid/simulationgrid.cpp \
    grid/triangulation.cpp \
    grid/uniformgrid.cpp \
    grid/utilities/glyphbuilder.cpp \
    grid/utilities/smokebuilder.cpp \
    grid/utilities/streamlinebuilder.cpp \
    grid/vertex.cpp \
    keyboardhandler.cpp \
    settings/canvassettings.cpp \
    settings/settings.cpp \
    settings/simulationsettings.cpp \
    settings/visualization/glyphs.cpp \
    settings/visualization/slices.cpp \
    settings/visualization/smokesettings.cpp \
    settings/visualization/streamlines.cpp \
    settings/visualization/visualizationsettings.cpp \
    shapes/cone.cpp \
    shapes/polyline.cpp \
    shapes/rectangle.cpp \
    simulation/simulation.cpp \
    simulation/simulationdata.cpp \
    simulation/simulationrealization.cpp \
    simulation/simulationstatehistory.cpp \
    simulation/utils.cpp \
    streamobjects/streamline.cpp \
    utilities/approximation.cpp \
    utilities/gpudata.cpp \
    utilities/mesh.cpp \
    utilities/range.cpp \
    utilities/rotation.cpp \
    utilities/vector.cpp \
    view/canvas.cpp \
    view/colormaplegend.cpp \
    view/colormaptab.cpp \
    view/floatslider.cpp \
    view/glyphstab.cpp \
    view/intslider.cpp \
    view/mainwindow.cpp \
    view/simulationtab.cpp \
    view/slicestab.cpp \
    view/streamlinestab.cpp

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
