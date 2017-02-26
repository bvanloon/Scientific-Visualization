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

    this->simulationTab = ui->simulationTab;

    this->smokeColorMapTab = ui->smokeColormapTab;

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

    connectSmokeColorMapTabAndSettings();

    connectKeyBoardHandlerAndSimulation();
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

void MainWindow::connectCanvasAndColorMapTab()
{
    connect(this->smokeColorMapTab, SIGNAL(setClamping(bool)),
            this->canvas, SLOT(onSetClamping(bool)));
    connect(this->smokeColorMapTab, SIGNAL(setClampingRange(float,float)),
            this->canvas, SLOT(onsetClampingRange(float,float)));
    connect(this->smokeColorMapTab, SIGNAL(colorMapChanged(AbstractColorMap)),
            this->canvas, SLOT(onColorMapChanged(AbstractColorMap)));
}

void MainWindow::connectSmokeColorMapTabAndSettings()
{
    connect(this->smokeColorMapTab, SIGNAL(scalarVariableChanged(Settings::Visualization::ScalarVariable)),
            &Settings::visualization(), SLOT(onScalarVariableChanged(Settings::Visualization::ScalarVariable)));
    connect(&Settings::simulation(), SIGNAL(valueRangeChanged(float,float)),
            this->smokeColorMapTab, SLOT(onValueRangeChanged(float,float)));
    connect(&Settings::visualization(), SIGNAL(valueRangeChanged(float,float)),
            this->smokeColorMapTab, SLOT(onValueRangeChanged(float,float)));
    connect(&Settings::simulation(), SIGNAL(forceChanged(float)),
            this->smokeColorMapTab, SLOT(onForceChanged(float)));
}

void MainWindow::connectKeyBoardHandlerAndSimulation()
{
    connect(this->keyboardHandler, SIGNAL(step()),
            this->simulation, SLOT(onStep()));
}



