#include "view/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settings = new Settings();

    this->simulation = new Simulation(this->settings);

    this->canvas = ui->openGLWidget;
    this->canvas->setSimulation(this->simulation);
    this->canvas->setSettings(this->settings);
    this->colorMapLegend = ui->colorMapLegend;
    this->simulationSettingPane = ui->simulationTab;


    connectCanvasAndSimulation();
    connectSettingsAndCanvas();
    connectSettingsAndColorMapLegend();
    connectSettingAndSimulationSettingPane();

    this->simulationSettingPane->emitDefaults();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->simulation;
    delete this->settings;
}

void MainWindow::connectCanvasAndSimulation()
{
    connect(this->canvas, SIGNAL(mouseMoved(QPoint)),
            this->simulation, SLOT(onMouseMoved(QPoint)));

    connect(this->simulation, SIGNAL(simulationUpdated()),
            this->canvas, SLOT(onSimulationUpdated()));

    }

void MainWindow::connectSettingsAndCanvas()
{
    connect(this->canvas, SIGNAL(windowResized(int, int)),
            this->settings, SLOT(onWindowResized(int, int)));

    connect(this->settings,SIGNAL(rangeChanged(float,float)),
            this->canvas, SLOT(onRangeChanged(float,float)));
}

void MainWindow::connectSettingsAndColorMapLegend()
{
    connect(this->settings, SIGNAL(rangeChanged(float,float)),
            this->colorMapLegend, SLOT(onRangeChanged(float,float)));

}

void MainWindow::connectSettingAndSimulationSettingPane()
{
    connect(this->simulationSettingPane, SIGNAL(forceChanged(float)),
            this->settings, SLOT(onForceChanged(float)));

}


