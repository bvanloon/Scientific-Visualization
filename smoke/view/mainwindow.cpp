#include "view/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->simulation = new Simulation();
    this->canvas = ui->openGLWidget;
    this->canvas->setSimulation(this->simulation);

    connectCanvasAndSimulation();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->simulation;
}

void MainWindow::connectCanvasAndSimulation()
{
    connect(this->canvas, SIGNAL(mouseMoved(QPointF)),
            this->simulation, SLOT(onMouseMoved(QPointF)));
}
