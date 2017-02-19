#include "view/mainwindow.h"
#include "ui_mainwindow.h"

#include "settings/settingsns.h"
#include "settings/simulations.h"
#include "settings/canvass.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->simulation = new Simulation();

    this->canvas = ui->openGLWidget;
    this->canvas->setSimulation(this->simulation);
    this->colorMapLegend = ui->colorMapLegend;
    this->simulationSettingPane = ui->simulationTab;


    connectCanvasAndSimulation();
    connectSettingsAndCanvas();
    connectSettingsAndColorMapLegend();
    connectSettingAndSimulationSettingPane();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->simulation;
}

void MainWindow::connectCanvasAndSimulation()
{
    connect(this->canvas, SIGNAL(mouseMoved(QPoint)),
            this->simulation, SLOT(onMouseMoved(QPoint)));
}

void MainWindow::connectSettingsAndCanvas()
{
    connect(&Settings::simulation(),SIGNAL(rangeChanged(float,float)),
            this->canvas, SLOT(onRangeChanged(float,float)));

    connect(this->canvas, SIGNAL(windowResized(int, int)),
            &Settings::canvas(), SLOT(onWindowResized(int, int)));

    connect(this->canvas, SIGNAL(windowResized(int, int)),
            &Settings::simulation(), SLOT(onWindowResized(int, int)));
}

void MainWindow::connectSettingsAndColorMapLegend()
{
    connect(&Settings::simulation(), SIGNAL(rangeChanged(float,float)),
            this->colorMapLegend, SLOT(onRangeChanged(float,float)));
}

void MainWindow::connectSettingAndSimulationSettingPane()
{
    connect(this->simulationSettingPane, SIGNAL(forceChanged(float)),
            &Settings::simulation(), SLOT(onForceChanged(float)));
}


