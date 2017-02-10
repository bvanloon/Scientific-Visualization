#include "view/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "MainWindow::MainWindow(QWidget *parent)";

    this->simulation = new Simulation();
    this->canvas = ui->openGLWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->simulation;
}
