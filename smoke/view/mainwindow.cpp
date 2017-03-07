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

   this->glyphsTab = ui->glyphsTab;

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
   connectEngineAndColorMapTab(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(this->canvas->EnginesEnum::smoke)->second), this->smokeColorMapTab);
   connectEngineAndSettings(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(this->canvas->EnginesEnum::smoke)->second));

   connectEngineAndColorMapTab(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(this->canvas->EnginesEnum::glyphs)->second), this->glyphsTab->getColorMapWidget());
   connectEngineAndSettings(dynamic_cast<AbstractEngine *>(this->canvas->enginemap.find(this->canvas->EnginesEnum::glyphs)->second));

   connectCanvasAndSimulationTab();
   connectVectorEngineAndGlyphTab();
   connectVectorEngineAndSettings();
}


void MainWindow::setUpConnections()
{
   connectCanvasAndThis();
   connectCanvasAndSimulation();
   connectCanvasAndSettings();

   connectSimulationTabAndSettings();
   connectSimulationTabAndSimulation();

   connectSmokeColorMapTabAndSettings();

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


void MainWindow::connectEngineAndSettings(AbstractEngine *currentEngine)
{
   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(float,float)),
             currentEngine, SLOT(onValueRangeChanged(float,float)));
   connect(&Settings::getVisualization(), SIGNAL(valueRangeChanged(float,float)),
            currentEngine, SLOT(onValueRangeChanged(float,float)));

   connect(&Settings::simulation(), SIGNAL(forceChanged(float)),
            currentEngine, SLOT(onForceChanged(float)));
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
            this->canvas->enginemap.find(this->canvas->EnginesEnum::glyphs)->second, SLOT(onGridDimensionChanged(int,int)));
}


void MainWindow::connectVectorEngineAndSettings()
{
   connect(&Settings::simulation(), SIGNAL(recomputeVertexPositions(QSize,QSizeF)),
   this->canvas->enginemap.find(this->canvas->EnginesEnum::glyphs)->second, SLOT(onRecomputeVertexPositions(QSize,QSizeF)));
}


void MainWindow::connectSmokeColorMapTabAndSettings()
{
   connect(this->smokeColorMapTab, SIGNAL(textureVariableChanged(Settings::visualization::ScalarVariable)),
            &Settings::getVisualization(), SLOT(onTextureVariableChanged(Settings::visualization::ScalarVariable)));
   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(float,float)),
            this->smokeColorMapTab, SLOT(onValueRangeChanged(float,float)));
   connect(&Settings::getVisualization(), SIGNAL(valueRangeChanged(float,float)),
            this->smokeColorMapTab, SLOT(onValueRangeChanged(float,float)));
   connect(&Settings::simulation(), SIGNAL(forceChanged(float)),
            this->smokeColorMapTab, SLOT(onForceChanged(float)));
   this->smokeColorMapTab->connectToColorMapSettings(Settings::visualization::smoke().getColorMap());
}


void MainWindow::connectKeyBoardHandlerAndSimulation()
{
   connect(this->keyboardHandler, SIGNAL(step()),
            this->simulation, SLOT(onStep()));
}
