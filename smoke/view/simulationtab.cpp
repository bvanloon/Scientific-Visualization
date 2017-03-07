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
   setUpConnections();
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
   connect(this, SIGNAL(toggleFrozen(bool)),
            this, SLOT(onToggleFrozen(bool)));
   connect(this->ui->forceSlider, SIGNAL(valueChanged(int)),
            this, SLOT(on_forceSlider_valueChanged(int)));
}


void SimulationSettingPane::setFreezeButtonLabel(bool frozen)
{
   QString labelText = (frozen ? "Thaw" : "Freeze");

   this->ui->freezeButton->setText(labelText);
}


void SimulationSettingPane::on_freezeButton_clicked()
{
   emit toggleFrozen(!Settings::simulation().frozen);
   emit toggleFrozen();
}


void SimulationSettingPane::on_stepButton_clicked()
{
   emit step();
}


void SimulationSettingPane::onToggleFrozen(bool frozen)
{
   this->ui->stepButton->setDisabled(!frozen);
   setFreezeButtonLabel(frozen);
}


void SimulationSettingPane::on_timeStepBox_valueChanged(double value)
{
   emit timeStepChanged(value);
}


void SimulationSettingPane::on_glyphsCheckBox_toggled(bool checked)
{
   emit glyphsEngineToggled(checked);
}


void SimulationSettingPane::on_smokeCheckBox_toggled(bool checked)
{
   emit smokeEngineToggled(checked);
}
