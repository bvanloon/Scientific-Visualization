#include "simulationsettingpane.h"
#include "ui_simulationsettingpane.h"
#include "settings/simulations.h"
#include "settings/settingsns.h"
#include <QDebug>

SimulationSettingPane::SimulationSettingPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationSettingPane)
{
    ui->setupUi(this);
    setUItoDefaults();
}

SimulationSettingPane::~SimulationSettingPane()
{
    delete ui;
}

void SimulationSettingPane::on_forceSlider_valueChanged(int value)
{
    emit forceChanged((float)value);
}

void SimulationSettingPane::setUItoDefaults()
{
    this->ui->forceSlider->setValue(Settings::simulation().force);
}
