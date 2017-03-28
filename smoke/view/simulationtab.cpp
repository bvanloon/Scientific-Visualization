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
   setUpEnineCheckBoxMappings();
   setUpConnections();
   setUItoDefaults();

   //Hack to avoid having to check if we are not requesting the nonexistent seedPoint checkbox.
   this->ui->seedPointsCheckBox->setHidden(true);
}

SimulationSettingPane::~SimulationSettingPane()
{
   delete ui;
}

void SimulationSettingPane::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   this->engines.find(engine).value()->setChecked(checked);
}

void SimulationSettingPane::setUItoDefaults()
{
   ui->forceSlider->setMinimum(Settings::defaults::simulation::forceMin);
   ui->forceSlider->setMaximum(Settings::defaults::simulation::forceMax);
   ui->forceSlider->setValue(Settings::simulation().force);

   ui->stepButton->setDisabled(!Settings::simulation().frozen);

   setEnginesToDefaults();
}

void SimulationSettingPane::setEnginesToDefaults()
{
   Settings::engines::EnginesTypes engine;
   for (int i = 0; i < Settings::engines::EnginesTypes::numberOfEngines; i++)
   {
      engine = static_cast<Settings::engines::EnginesTypes>(i);
      emit engineToggled(engine, Settings::defaults::engines::activeEngines[engine]);
   }
}

void SimulationSettingPane::setUpConnections()
{
   connect(this, SIGNAL(toggleFrozen(bool)),
            this, SLOT(onToggleFrozen(bool)));
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
           this, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
}

void SimulationSettingPane::setUpEnineCheckBoxMappings()
{
   this->engines.insert(Settings::engines::EnginesTypes::smoke, this->ui->smokeCheckBox);
   this->engines.insert(Settings::engines::EnginesTypes::glyphs, this->ui->glyphsCheckBox);
   this->engines.insert(Settings::engines::EnginesTypes::streamLines, this->ui->streamLinesCheckBox);
   this->engines.insert(Settings::engines::EnginesTypes::smokeSlices, this->ui->smokeSlicesCheckBox);
   this->engines.insert(Settings::engines::EnginesTypes::glyphSlices, this->ui->glyphSlicesCheckBox);
   this->engines.insert(Settings::engines::EnginesTypes::streamLineSlices, this->ui->streamLineSlicesCheckBox);
   this->engines.insert(Settings::engines::EnginesTypes::seedPoints, this->ui->seedPointsCheckBox);

    this->nonSliceEngines.insert(Settings::engines::EnginesTypes::smoke, this->ui->smokeCheckBox);
    this->nonSliceEngines.insert(Settings::engines::EnginesTypes::glyphs, this->ui->glyphsCheckBox);
    this->nonSliceEngines.insert(Settings::engines::EnginesTypes::streamLines, this->ui->streamLinesCheckBox);
    this->nonSliceEngines.insert(Settings::engines::EnginesTypes::seedPoints, this->ui->seedPointsCheckBox);

    this->sliceEngines.insert(Settings::engines::EnginesTypes::smokeSlices, this->ui->smokeSlicesCheckBox);
    this->sliceEngines.insert(Settings::engines::EnginesTypes::glyphSlices, this->ui->glyphSlicesCheckBox);
    this->sliceEngines.insert(Settings::engines::EnginesTypes::streamLineSlices, this->ui->streamLineSlicesCheckBox);
}

void SimulationSettingPane::setFreezeButtonLabel(bool frozen)
{
   QString labelText = (frozen ? "Thaw" : "Freeze");

   this->ui->freezeButton->setText(labelText);
}

void SimulationSettingPane::disableNonSliceEngines()
{

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
}

void SimulationSettingPane::on_smokeCheckBox_toggled(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::smoke, checked);
}

void SimulationSettingPane::on_forceSlider_valueChanged(double value)
{
   emit forceChanged(value);
}

void SimulationSettingPane::on_streamLinesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::streamLines, checked);
   emit engineToggled(Settings::engines::EnginesTypes::seedPoints, checked);
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
