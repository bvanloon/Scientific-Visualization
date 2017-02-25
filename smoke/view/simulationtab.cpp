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

    connect(this, SIGNAL(toggleFrozen()),
            this, SLOT(onToggleFrozen()));
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
    ui->stepButton->setDisabled(!Settings::simulation().frozen);
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
}

void SimulationSettingPane::on_stepButton_clicked()
{
    emit step();
}

void SimulationSettingPane::onToggleFrozen()
{
    this->ui->stepButton->setDisabled(!Settings::simulation().frozen);
    setFreezeButtonLabel();
}
