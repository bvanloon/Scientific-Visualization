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
    settings/visualization/glyphsettings.cpp \
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
    grid/glyphdata.cpp \
    colormaps/huecolormap.cpp \
    glyphs/glyphsfactory.cpp \
    glyphs/abstractglyph.cpp \
    glyphs/glyphstriangulation.cpp \
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
    grid/utilities/glyphbuilder.cpp

HEADERS  += main.ih\
        view/mainwindow.h \
    view/canvas.h \
    simulation/simulation.h \
    simulation/simulationrealization.h \
    simulation/utils.h \
    engines/smokeengine.h \
    colormaps/abstractcolormap.h \
    colormaps/rainbowcolormap.h \
    colormaps/colormapfactory.h \
    view/colormaplegend.h \
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
    glyphs/hedgehog.h \
    glyphs/triangle.h \
    glyphs/ccwtriangle.h \
    glyphs/airplane.h \
    utilities/range.h \
    utilities/mesh.h \
    utilities/vector.h \
    glyphs/cone.h \
    shapes/cone.h \
    unused.h \
    utilities/approximation.h \
    settings/visualization/streamlines.h \
    view/streamlinestab.h \
    engines/seedpointengine.h \
    shapes/rectangle.h \
    engines/streamlineengine.h \
    shapes/polyline.h \
    utilities/gpudata.h \
    streamobjects/streamline.h \
    grid/utilities/streamlinebuilder.h \
    grid/jittergrid.h \
    engines/smokeslicesengine.h \
    engines/glyphsliceengine.h \
    engines/streamlineslicesengine.h \
    engines/abstractsliceengine.h \
    utilities/rotation.h \
    settings/visualization/slices.h \
    view/slicestab.h \
    simulation/simulationstatehistory.h \
    simulation/simulationdata.h \
    grid/simulationgrid.h \
    utilities/sizelimitedqueue.h \
    grid/utilities/smokebuilder.h \
    engines/glyphengine.h \
    grid/utilities/glyphbuilder.h

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
