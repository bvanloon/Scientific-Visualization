#include "view/mainwindow.h"
#include "ui_mainwindow.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"

MainWindow::MainWindow(QWidget *parent) :

   QMainWindow(parent),
   keyboardHandler(new KeyboardHandler(this)),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   this->simulation = new Simulation();

   this->canvas = ui->openGLWidget;
   this->canvas->setSimulation(this->simulation);

   this->simulationTab = ui->simulationTab;

   this->smokeColorMapTab = ui->smokeColormapTab;
   this->smokeColorMapTab->setColormapSettings(Settings::visualization::smoke().colorMap);

   this->glyphsTab = ui->glyphsTab;
   this->glyphsTab->getColorMapWidget()->setColormapSettings(Settings::visualization::glyphs().colorMap);

   this->streamLinesTab = ui->streamLinesTab;
   this->streamLinesTab->getColorMapWidget()->setColormapSettings(Settings::visualization::streamLines().colorMap);

   this->installEventFilter(this->keyboardHandler);

   setUpConnections();
}

MainWindow::~MainWindow()
{
   delete ui;
   delete this->simulation;
   delete this->keyboardHandler;
}

void MainWindow::onOpenGLReady()
{
   connectEngineAndColorMapTab(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(Settings::engines::EnginesTypes::smoke)->second), this->smokeColorMapTab);
   connectEngineAndSettings(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(Settings::engines::EnginesTypes::smoke)->second));

   connectEngineAndColorMapTab(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(Settings::engines::EnginesTypes::glyphs)->second), this->glyphsTab->getColorMapWidget());
   connectEngineAndSettings(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(Settings::engines::EnginesTypes::glyphs)->second));

   qDebug() << "connectStreamLineEngineAndColorMapTab";
   qDebug() << "connectStreamLineEngineAndSettings";

   connectCanvasAndSimulationTab();

   connectVectorEngineAndGlyphTab();
   connectVectorEngineAndSettings();

   connectSmokeEngineAndSettings();
}

void MainWindow::setUpConnections()
{
   connectCanvasAndThis();
   connectCanvasAndSimulation();
   connectCanvasAndSettings();

   connectSimulationTabAndSettings();
   connectSimulationTabAndSimulation();

   connectGlyphTabAndSettings();

   connectSmokeTabAndSettings();

   connectStreamLinesTabAndSettings();

   connectKeyBoardHandlerAndSimulation();
}

void MainWindow::connectCanvasAndThis()
{
   connect(this->canvas, SIGNAL(openGlReady()),
            this, SLOT(onOpenGLReady()));
}

void MainWindow::connectCanvasAndSimulation()
{
   connect(this->canvas, SIGNAL(mouseMoved(QPoint)),
            this->simulation, SLOT(onMouseMoved(QPoint)));
   connect(this->canvas, SIGNAL(windowResized(int,int)),
            this->simulation, SLOT(onWindowResized(int,int)));
}

void MainWindow::connectCanvasAndSettings()
{
   connect(this->canvas, SIGNAL(windowResized(int,int)),
            &Settings::canvas(), SLOT(onWindowResized(int,int)));

   connect(this->canvas, SIGNAL(windowResized(int,int)),
            &Settings::simulation(), SLOT(onWindowResized(int,int)));
}

void MainWindow::connectCanvasAndSimulationTab()
{
   connect(this->simulationTab, SIGNAL(glyphsEngineToggled(bool)),
            this->canvas, SLOT(onGlyphsEngineToggled(bool)));

   connect(this->simulationTab, SIGNAL(smokeEngineToggled(bool)),
                    this->canvas, SLOT(onSmokeEngineToggled(bool)));
}

void MainWindow::connectSimulationTabAndSettings()
{
   connect(this->simulationTab, SIGNAL(forceChanged(float)),
            &Settings::simulation(), SLOT(onForceChanged(float)));
   connect(this->simulationTab, SIGNAL(toggleFrozen()),
            &Settings::simulation(), SLOT(onToggleFrozen()));
   connect(&Settings::simulation(), SIGNAL(toggleFrozen(bool)),
            this->simulationTab, SLOT(onToggleFrozen(bool)));
   connect(this->simulationTab, SIGNAL(timeStepChanged(float)),
            &Settings::simulation(), SLOT(onTimeStepChanged(float)));
}

void MainWindow::connectSimulationTabAndSimulation()
{
   connect(this->simulationTab, SIGNAL(step()),
           this->simulation, SLOT(onStep()));
}

void MainWindow::connectGlyphTabAndSettings()
{
   this->glyphsTab->getColorMapWidget()->connectToColorMapSettings(Settings::visualization::glyphs().colorMap);
   connect(this->glyphsTab, SIGNAL(vectorFieldChanged(Settings::sim::Vector)),
           &Settings::visualization::glyphs(), SLOT(onVectorFieldChanged(Settings::sim::Vector)));

   connect(this->glyphsTab, SIGNAL(glyphChanged(Settings::sim::GlyphsType)),
           &Settings::visualization::glyphs(), SLOT(onGlyphChanged(Settings::sim::GlyphsType)));

   connect(this->glyphsTab, SIGNAL(scaleChanged(double)),
           &Settings::visualization::glyphs(), SLOT(onScaleChanged(double)));
}

void MainWindow::connectEngineAndSettings(AbstractEngine *currentEngine)
{
   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           currentEngine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
}

void MainWindow::connectEngineAndColorMapTab(AbstractEngine *currentEngine, ColorMapTab *colormap)
{
   connect(colormap, SIGNAL(setClamping(bool)),
            currentEngine, SLOT(onSetClamping(bool)));
   connect(colormap, SIGNAL(setClampingRange(float,float)),
            currentEngine, SLOT(onsetClampingRange(float,float)));
   connect(colormap, SIGNAL(colorMapChanged(AbstractColorMap)),
            currentEngine, SLOT(onColorMapChanged(AbstractColorMap)));
}

void MainWindow::connectVectorEngineAndGlyphTab()
{
   connect(this->ui->glyphsTab, SIGNAL(gridDimensionChanged(int,int)),
            this->canvas->enginemap.find(Settings::engines::EnginesTypes::glyphs)->second, SLOT(onGridDimensionChanged(int,int)));
}

void MainWindow::connectVectorEngineAndSettings()
{
   AbstractEngine *engine = this->canvas->enginemap.find(Settings::engines::EnginesTypes::glyphs)->second;


   engine->setColorMap(Settings::visualization::glyphs().colorMap);

   connect(&Settings::simulation(), SIGNAL(recomputeVertexPositions(QSize,QSizeF)),
           engine, SLOT(onRecomputeVertexPositions(QSize,QSizeF)));
   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           engine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
   connect(Settings::visualization::glyphs().colorMap, SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           engine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
   connect(dynamic_cast<VectorEngine *>(engine), SIGNAL(cellSizeChanged(QSizeF)),
           &Settings::visualization::glyphs(), SLOT(onCellSizeChanged(QSizeF)));
}

void MainWindow::connectSmokeEngineAndSettings()
{
   AbstractEngine *engine = this->canvas->enginemap.find(Settings::engines::EnginesTypes::smoke)->second;

   engine->setColorMap(Settings::visualization::smoke().colorMap);

   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           engine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
   connect(Settings::visualization::smoke().colorMap, SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           engine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
}

void MainWindow::connectSmokeTabAndSettings()
{
   this->smokeColorMapTab->connectToColorMapSettings(Settings::visualization::smoke().colorMap);
}

void MainWindow::connectStreamLinesTabAndSettings()
{
    connect(this->streamLinesTab, SIGNAL(timeStepChanged(double)),
            &Settings::visualization::streamLines(), SLOT(ontimeStepChanged(double)));
    connect(this->streamLinesTab, SIGNAL(edgeLengthFactorChanged(double)),
            &Settings::visualization::streamLines(), SLOT(onEdgeLengthFactorChanged(double)));
    connect(this->streamLinesTab, SIGNAL(clearSeedPoints()),
            &Settings::visualization::streamLines(), SLOT(onClearSeedPoints()));

}

void MainWindow::connectKeyBoardHandlerAndSimulation()
{
   connect(this->keyboardHandler, SIGNAL(step()),
            this->simulation, SLOT(onStep()));
}
