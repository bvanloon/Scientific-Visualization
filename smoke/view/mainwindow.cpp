#include "view/mainwindow.h"
#include "ui_mainwindow.h"

#include "settings/settings.h"
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
    qDebug() << "MainWindow::MainWindow: do something here";
//    this->visualiationSettingsPane = ui->colormapTab;


    connectCanvasAndSimulation();
    connectSettingsAndCanvas();
    connectSettingsAndColorMapLegend();
    connectColorMapSettingsPaneAndColorMapLegend();
    connectSettingAndSimulationSettingPane();
    connectCanvasAndColorMapSettingsPane();
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
    connect(&Settings::simulation(),SIGNAL(valueRangeChanged(float,float)),
            this->canvas, SLOT(onValueRangeChanged(float,float)));

    connect(this->canvas, SIGNAL(windowResized(int, int)),
            &Settings::canvas(), SLOT(onWindowResized(int, int)));

    connect(this->canvas, SIGNAL(windowResized(int, int)),
            &Settings::simulation(), SLOT(onWindowResized(int, int)));
}

void MainWindow::connectSettingsAndColorMapLegend()
{
    connect(&Settings::simulation(), SIGNAL(valueRangeChanged(float,float)),
            this->colorMapLegend, SLOT(onValueRangeChanged(float,float)));
}

void MainWindow::connectSettingAndSimulationSettingPane()
{
    connect(this->simulationSettingPane, SIGNAL(forceChanged(float)),
            &Settings::simulation(), SLOT(onForceChanged(float)));
}

void MainWindow::connectCanvasAndColorMapSettingsPane()
{
    qDebug() << "MainWindow::connectCanvasAndColorMapSettingsPane: do something here";
    connect(this->visualiationSettingsPane, SIGNAL(setClamping(bool)),
            this->canvas, SLOT(onSetClamping(bool)));
    connect(this->visualiationSettingsPane, SIGNAL(setClampingRange(float,float)),
            this->canvas, SLOT(onsetClampingRange(float,float)));
}

void MainWindow::connectColorMapSettingsPaneAndColorMapLegend()
{
    qDebug() << "MainWindow::connectColorMapSettingsPaneAndColorMapLegend: do something here";
    connect(this->visualiationSettingsPane, SIGNAL(setClampingRange(float,float)),
            this->colorMapLegend, SLOT(onClampRangeChanged(float,float)));
}



