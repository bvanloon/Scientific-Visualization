#include "simulationsettingpane.h"
#include "ui_simulationsettingpane.h"
#include "settings/simulations.h"
#include "settings/settings.h"
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
    ui->forceSlider->init(Settings::defaults::simulation::valueRangeMin,
                          Settings::defaults::simulation::valueRangeMax,
                          Settings::simulation().force);
}

void SimulationSettingPane::setUpConnections()
{
    connect(this->ui->forceSlider, SIGNAL(valueChanged(int)),
            this, SLOT(on_forceSlider_valueChanged(int)));
}
