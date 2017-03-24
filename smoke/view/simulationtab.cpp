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

void SimulationSettingPane::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   switch (engine)
   {
   case Settings::engines::EnginesTypes::glyphs:
      this->ui->glyphsCheckBox->setChecked(checked);
      break;

   case Settings::engines::EnginesTypes::streamLines:
      this->ui->streamLinesCheckBox->setChecked(checked);
      break;

   case Settings::engines::EnginesTypes::smoke:
      this->ui->smokeCheckBox->setChecked(checked);
      break;

   case Settings::engines::EnginesTypes::seedPoints:
      //Do nothing
      break;

   case Settings::engines::EnginesTypes::smokeSlices:
   //Fall through
   case Settings::engines::EnginesTypes::glyphSlices:
   //Fall through
   case Settings::engines::EnginesTypes::streamLineSlices:
   //Fall through
   case Settings::engines::EnginesTypes::numberOfEngines:
      qDebug() << "SimulationSettingPane::onEngineToggled: " << engine << " is an invalid engine enum here.";
      break;
   }
}

void SimulationSettingPane::setUItoDefaults()
{
   ui->forceSlider->setMinimum(Settings::defaults::simulation::forceMin);
   ui->forceSlider->setMaximum(Settings::defaults::simulation::forceMax);
   ui->forceSlider->setValue(Settings::simulation().force);

   ui->stepButton->setDisabled(!Settings::simulation().frozen);

   ui->glyphsCheckBox->setChecked(Settings::defaults::engines::activeEngines[Settings::engines::EnginesTypes::glyphs]);
   ui->smokeCheckBox->setChecked(Settings::defaults::engines::activeEngines[Settings::engines::EnginesTypes::smoke]);
   ui->streamLinesCheckBox->setChecked(Settings::defaults::engines::activeEngines[Settings::engines::EnginesTypes::streamLines]);
}

void SimulationSettingPane::setUpConnections()
{
   connect(this, SIGNAL(toggleFrozen(bool)),
            this, SLOT(onToggleFrozen(bool)));
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
   emit engineToggled(Settings::engines::EnginesTypes::glyphs, checked);

   if (checked) toggleSliceEnginges(false);
}

void SimulationSettingPane::on_smokeCheckBox_toggled(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::smoke, checked);

   if (checked) toggleSliceEnginges(false);
}

void SimulationSettingPane::on_forceSlider_valueChanged(double value)
{
   emit forceChanged(value);
}

void SimulationSettingPane::on_streamLinesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::streamLines, checked);
   emit engineToggled(Settings::engines::EnginesTypes::seedPoints, checked);

   if (checked) toggleSliceEnginges(false);
}

void SimulationSettingPane::on_glyphSlicesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::glyphSlices, checked);
}

void SimulationSettingPane::on_smokeSlicesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::smokeSlices, checked);
}

void SimulationSettingPane::on_streamLineSlicesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::streamLineSlices, checked);
}
