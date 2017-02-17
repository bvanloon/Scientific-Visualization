#include "simulationsettingpane.h"
#include "ui_simulationsettingpane.h"

SimulationSettingPane::SimulationSettingPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationSettingPane)
{
    ui->setupUi(this);
}

SimulationSettingPane::~SimulationSettingPane()
{
    delete ui;
}
