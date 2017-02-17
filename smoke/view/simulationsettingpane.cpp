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

void SimulationSettingPane::emitDefaults()
{
    emit forceChanged((float)this->ui->forceSlider->value());
}

void SimulationSettingPane::on_forceSlider_valueChanged(int value)
{
    emit forceChanged((float)value);
}
