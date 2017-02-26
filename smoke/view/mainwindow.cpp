#include "view/mainwindow.h"
#include "ui_mainwindow.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    keyboardHandler(new KeyboardHandler(this))
{
    ui->setupUi(this);

    this->simulation = new Simulation();

    this->canvas = ui->openGLWidget;
    this->canvas->setSimulation(this->simulation);

    this->colorMapLegend = ui->colorMapLegend;

    this->simulationTab = ui->simulationTab;

    this->colorMapTab = ui->colormapTab;

    this->installEventFilter(this->keyboardHandler);

    setUpConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->simulation;
    delete this->keyboardHandler;
}

void MainWindow::setUpConnections()
{
    connectCanvasAndSimulation();
    connectCanvasAndSettings();
    connectCanvasAndColorMapTab();

    connectSimulationTabAndSettings();
    connectSimulationTabAndSimulation();
    connectSimulationTabAndKeyboardHandler();

    connectColorMapTabAndColorMapLegend();
    connectColorMapTabAndSettings();

    connectColorMapLegendAndSettings();

    connectKeyBoardHandlerAndSimulation();
}

void MainWindow::connectCanvasAndSimulation()
{
    connect(this->canvas, SIGNAL(mouseMoved(QPoint)),
            this->simulation, SLOT(onMouseMoved(QPoint)));
}

void MainWindow::connectCanvasAndSettings()
{
    connect(&Settings::simulation(),SIGNAL(valueRangeChanged(float,float)),
            this->canvas, SLOT(onValueRangeChanged(float,float)));

    connect(&Settings::visualization(), SIGNAL(valueRangeChanged(float,float)),
            this->canvas, SLOT(onValueRangeChanged(float,float)));

    connect(this->canvas, SIGNAL(windowResized(int, int)),
            &Settings::canvas(), SLOT(onWindowResized(int, int)));

    connect(this->canvas, SIGNAL(windowResized(int, int)),
            &Settings::simulation(), SLOT(onWindowResized(int, int)));

    connect(&Settings::simulation(), SIGNAL(forceChanged(float)),
            this->canvas, SLOT(onForceChanged(float)));
}

void MainWindow::connectColorMapLegendAndSettings()
{
    connect(&Settings::simulation(), SIGNAL(valueRangeChanged(float,float)),
            this->colorMapLegend, SLOT(onValueRangeChanged(float,float)));

    connect(&Settings::visualization(), SIGNAL(valueRangeChanged(float,float)),
            this->colorMapLegend, SLOT(onValueRangeChanged(float,float)));
    connect(&Settings::simulation(), SIGNAL(forceChanged(float)),
            this->colorMapLegend, SLOT(onForceChanged(float)));
}

void MainWindow::connectSimulationTabAndSettings()
{
    connect(this->simulationTab, SIGNAL(forceChanged(float)),
            &Settings::simulation(), SLOT(onForceChanged(float)));
    connect(this->simulationTab, SIGNAL(toggleFrozen()),
            &Settings::simulation(), SLOT(onToggleFrozen()));
    connect(this->simulationTab, SIGNAL(timeStepChanged(float)),
            &Settings::simulation(), SLOT(onTimeStepChanged(float)));
}

void MainWindow::connectSimulationTabAndSimulation()
{
    connect(this->simulationTab, SIGNAL(step()),
            this->simulation, SLOT(onStep()));
}

void MainWindow::connectSimulationTabAndKeyboardHandler()
{
    connect(this->keyboardHandler, SIGNAL(toggleFrozen()),
            this->simulationTab, SLOT(onToggleFrozen()));
}

void MainWindow::connectCanvasAndColorMapTab()
{
    connect(this->colorMapTab, SIGNAL(setClamping(bool)),
            this->canvas, SLOT(onSetClamping(bool)));
    connect(this->colorMapTab, SIGNAL(setClampingRange(float,float)),
            this->canvas, SLOT(onsetClampingRange(float,float)));
    connect(this->colorMapTab, SIGNAL(colorMapChanged(AbstractColorMap)),
            this->canvas, SLOT(onColorMapChanged(AbstractColorMap)));
}

void MainWindow::connectColorMapTabAndColorMapLegend()
{
    connect(this->colorMapTab, SIGNAL(setClampingRange(float,float)),
            this->colorMapLegend, SLOT(onClampRangeChanged(float,float)));
    connect(this->colorMapTab, SIGNAL(colorMapChanged(AbstractColorMap)),
            this->colorMapLegend, SLOT(onColorMapChanged(AbstractColorMap)));
}

void MainWindow::connectColorMapTabAndSettings()
{
    connect(this->colorMapTab, SIGNAL(scalarVariableChanged(Settings::Visualization::ScalarVariable)),
            &Settings::visualization(), SLOT(onScalarVariableChanged(Settings::Visualization::ScalarVariable)));
}

void MainWindow::connectKeyBoardHandlerAndSimulation()
{
    connect(this->keyboardHandler, SIGNAL(step()),
            this->simulation, SLOT(onStep()));
}



