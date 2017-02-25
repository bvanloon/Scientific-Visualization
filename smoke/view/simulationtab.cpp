#include "simulationtab.h"
#include "ui_simulationtab.h"
#include "settings/simulationsettings.h"
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
    ui->forceSlider->init(Settings::defaults::simulation::forceMin,
                          Settings::defaults::simulation::forceMax,
                          Settings::simulation().force);
}

void SimulationSettingPane::setUpConnections()
{
    connect(this->ui->forceSlider, SIGNAL(valueChanged(int)),
            this, SLOT(on_forceSlider_valueChanged(int)));
}

void SimulationSettingPane::setFreezeButtonLabel()
{
    QString labelText = (Settings::simulation().frozen ? "Thaw" : "Freeze");
    this->ui->freezeButton->setText(labelText);
}

void SimulationSettingPane::on_freezeButton_clicked()
{
    emit toggleFrozen();
    this->ui->stepButton->setDisabled(!Settings::simulation().frozen);
    setFreezeButtonLabel();
}

void SimulationSettingPane::on_stepButton_clicked()
{
    emit step();
}
