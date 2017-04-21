#include "view/mainwindow.h"
#include "ui_mainwindow.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

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
   this->smokeTab = ui->smokeColormapTab;
   this->glyphsTab = ui->glyphsTab;
   this->streamLinesTab = ui->streamLinesTab;
   this->streamSurfacesTab = ui->streamSurfacesTab;

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
   connectAbstractEngine(Settings::engines::glyphs,
                          this->glyphsTab->getColorMapWidget(),
                          Settings::visualization::glyphs().colorMap);
   connectAbstractEngine(Settings::engines::smoke,
                          this->smokeTab->getColorMapWidget(),
                          Settings::visualization::smoke().colorMap);
   connectAbstractEngine(Settings::engines::seedPoints,
                          this->streamLinesTab->getColorMapWidget(),
                          Settings::visualization::streamLines().colorMap);
   connectAbstractEngine(Settings::engines::streamLines,
                         this->streamLinesTab->getColorMapWidget(),
                         Settings::visualization::streamLines().colorMap);
   connectAbstractEngine(Settings::engines::seedCurves,
                         this->streamSurfacesTab->getColorMapWidget(),
                         Settings::visualization::streakSurface().colorMap);
   connectAbstractEngine(Settings::engines::streamSurfaces,
                         this->streamSurfacesTab->getColorMapWidget(),
                         Settings::visualization::streakSurface().colorMap);

   connectAbstractSliceEngine(Settings::engines::smokeSlices,
                         this->smokeTab->getColorMapWidget(),
                         Settings::visualization::smoke().colorMap);
   connectAbstractSliceEngine(Settings::engines::glyphSlices,
                         this->glyphsTab->getColorMapWidget(),
                         Settings::visualization::glyphs().colorMap);
   connectAbstractSliceEngine(Settings::engines::streamLineSlices,
                         this->streamLinesTab->getColorMapWidget(),
                         Settings::visualization::streamLines().colorMap);

   connectGlyphEngineAndSettings();
   connectGlyphEngineAndGlyphTab();

   connectThisToFinishConnectionsReceivers();
   emit finishedSettingUpConnections();
}

void MainWindow::setUpConnections()
{
   connectCanvasAndThis();
   connectCanvasAndSimulation();
   connectCanvasAndSettings();
   connectCanvasAndTabs();

   connectSimulationTabAndSettings();
   connectSimulationTabAndSimulation();

   connectGlyphTabAndSettings();

   connectStreamLinesTabAndSettings();

   connectTabs();

   connectKeyBoardHandlerAndSimulation();

   connectSimuationStateHistory();
}

void MainWindow::connectSimuationStateHistory()
{
   connect(&Settings::visualization::slices(), SIGNAL(historySizeChanged(int)),
            &SimulationHistory::instance(), SLOT(onHistorySizeChanged(int)));
   connect(this->simulation, SIGNAL(newSimulationState(SimulationData *)),
           &SimulationHistory::instance(), SLOT(onNewSimulationState(SimulationData *)));
   connect(&Settings::canvas(), SIGNAL(windowResized(QSizeF)),
           &SimulationHistory::instance(), SLOT(onWindowResized(QSizeF)));
   connect(&Settings::visualization::glyphs(), SIGNAL(gridDimensionChanged(QSizeF)),
           &SimulationHistory::instance(), SLOT(onGridDimensionChanged(QSizeF)));
   connect(&Settings::visualization::streakSurface(), SIGNAL(numberOfStatesChanged(int)),
           &SimulationHistory::instance(), SLOT(onHistorySizeChanged(int)));
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

   connect(this->canvas, SIGNAL(seedPointAdded(QPointF)),
           &Settings::visualization::streamLines(), SLOT(onSeedPointAdded(QPointF)));

   connect(this->canvas, SIGNAL(scalingFactorChanged(double)),
           &Settings::canvas(), SLOT(onScalingFactorChanged(double)));

   connect(this->canvas, SIGNAL(panningDirectionChanged(QVector3D)),
           &Settings::canvas(), SLOT(onPanningPositionChanged(QVector3D)));

   connect(this->canvas, SIGNAL(seedCurveVertexAdded(QPointF)),
           &Settings::visualization::streakSurface(), SLOT(onSeedCurveVertexAdded(QPointF)));
}

void MainWindow::connectCanvasAndTabs()
{
   connect(this->simulationTab, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
           this->canvas, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
   connect(this->streamLinesTab, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
           this->canvas, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
}

void MainWindow::connectThisToFinishConnectionsReceivers()
{
   connect(this, SIGNAL(finishedSettingUpConnections()),
            this->simulationTab, SLOT(onAllConnectionsAreSetUp()));
   connect(this, SIGNAL(finishedSettingUpConnections()),
           &Settings::visualization::slices(), SLOT(onFinishedSettingUpConnections()));
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
   connect(this->simulationTab, SIGNAL(rotationChanged(Rotation::axis,int)),
           &Settings::canvas(), SLOT(onRotationChanged(Rotation::axis,int)));
   connect(this->simulationTab, SIGNAL(scalingFactorChanged(double)),
           &Settings::canvas(), SLOT(onScalingFactorChanged(double)));
   connect(&Settings::canvas(), SIGNAL(scalingFactorChanged(double)),
           this->simulationTab, SLOT(onScalingFactorChanged(double)));
   connect(this->simulationTab, SIGNAL(resetView()),
           &Settings::canvas(), SLOT(onResetView()));
   connect(&Settings::canvas(), SIGNAL(rotationChanged(Rotation)),
           this->simulationTab, SLOT(onRotationChanged(Rotation)));
}

void MainWindow::connectSimulationTabAndSimulation()
{
   connect(this->simulationTab, SIGNAL(step()),
           this->simulation, SLOT(onStep()));
}

void MainWindow::connectGlyphTabAndSettings()
{
   connect(this->glyphsTab, SIGNAL(vectorFieldChanged(Settings::sim::Vector)),
           &Settings::visualization::glyphs(), SLOT(onVectorFieldChanged(Settings::sim::Vector)));

   connect(this->glyphsTab, SIGNAL(glyphChanged(Settings::sim::GlyphsType)),
           &Settings::visualization::glyphs(), SLOT(onGlyphChanged(Settings::sim::GlyphsType)));

   connect(this->glyphsTab, SIGNAL(scaleChanged(double)),
           &Settings::visualization::glyphs(), SLOT(onScaleChanged(double)));
}

void MainWindow::connectAbstractEngine(Settings::engines::EnginesTypes engineType,
                                       ColorMapTab *colormapTab,
                                       Settings::visualization::ColorMap *colorMapSetings)
{
   AbstractEngine *engine = this->canvas->getEngine(engineType);

   //Connect colorMapSettings with ColorMapTab
   colormapTab->setColormapSettings(colorMapSetings);

   //Connect with colormapTab with Engine
   connect(colormapTab, SIGNAL(setClamping(bool)),
             engine, SLOT(onSetClamping(bool)));
   connect(colormapTab, SIGNAL(setClampingRange(float,float)),
             engine, SLOT(onsetClampingRange(float,float)));
   connect(colormapTab, SIGNAL(colorMapChanged(AbstractColorMap)),
            engine, SLOT(onColorMapChanged(AbstractColorMap)));

   //Set the colormap settings in the engine
   engine->setColorMap(colorMapSetings);

   //Connect the colormapSettings with the engine
   connect(colorMapSetings, SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
            engine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));

   //Connect to the Simulation
   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           engine, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
}

void MainWindow::connectAbstractSliceEngine(Settings::engines::EnginesTypes engineType, ColorMapTab *colormapTab, Settings::visualization::ColorMap *colorMapSetings)
{
   connectAbstractEngine(engineType, colormapTab, colorMapSetings);
   AbstractSliceEngine *engine = dynamic_cast<AbstractSliceEngine *>(this->canvas->getEngine(engineType));

   connect(&Settings::canvas(), SIGNAL(updateModelViewMatrix()),
            engine, SLOT(onUpdateModelViewMatrix()));
   connect(simulation, SIGNAL(newSimulationState(SimulationData *)),
           engine, SLOT(onNewSimulationState()));
}

void MainWindow::connectGlyphEngineAndGlyphTab()
{
   connect(this->ui->glyphsTab, SIGNAL(gridDimensionChanged(int,int)),
            this->canvas->getEngine(Settings::engines::EnginesTypes::glyphs), SLOT(onGridDimensionChanged(int,int)));
}

void MainWindow::connectGlyphEngineAndSettings()
{
   AbstractEngine *engine = this->canvas->getEngine(Settings::engines::EnginesTypes::glyphs);

   connect(&Settings::simulation(), SIGNAL(recomputeVertexPositions(QSize,QSizeF)),
           engine, SLOT(onRecomputeVertexPositions(QSize,QSizeF)));
   connect(dynamic_cast<GlyphEngine *>(engine), SIGNAL(cellSizeChanged(QSizeF)),
           &Settings::visualization::glyphs(), SLOT(onCellSizeChanged(QSizeF)));
}

void MainWindow::connectStreamLinesTabAndSettings()
{
   connect(this->streamLinesTab, SIGNAL(timeStepChanged(double)),
            &Settings::visualization::streamLines(), SLOT(ontimeStepChanged(double)));
   connect(this->streamLinesTab, SIGNAL(maximumTimeChanged(double)),
            &Settings::visualization::streamLines(), SLOT(onMaximumTimeChanged(double)));
   connect(this->streamLinesTab, SIGNAL(edgeLengthFactorChanged(double)),
            &Settings::visualization::streamLines(), SLOT(onEdgeLengthFactorChanged(double)));
   connect(this->streamLinesTab, SIGNAL(maximumTotalLengthFactorChanged(double)),
            &Settings::visualization::streamLines(), SLOT(onMaximumTotalLengthFactorChanged(double)));
   connect(this->streamLinesTab, SIGNAL(clearSeedPoints()),
           &Settings::visualization::streamLines(), SLOT(onClearSeedPoints()));
}

void MainWindow::connectTabs()
{
   connect(this->streamLinesTab, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            this->simulationTab, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
   connect(this->simulationTab, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            this->streamLinesTab, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
}

void MainWindow::connectKeyBoardHandlerAndSimulation()
{
   connect(this->keyboardHandler, SIGNAL(step()),
            this->simulation, SLOT(onStep()));
}
