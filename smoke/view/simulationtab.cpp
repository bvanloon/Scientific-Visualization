#include "simulationtab.h"
#include "ui_simulationtab.h"
#include "settings/simulationsettings.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include <QDebug>

SimulationSettingPane::SimulationSettingPane(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::SimulationSettingPane)
{
   ui->setupUi(this);
   setUpEnineCheckBoxMappings();
   setUpPrivateConnections();
   connectToSettings();
   setUItoDefaults();

   //Hack to avoid having to check if we are not requesting the nonexistent seedPoint checkbox.
   this->ui->seedPointsCheckBox->setHidden(true);
   this->ui->slicesCheckBox->setHidden(true);
}

SimulationSettingPane::~SimulationSettingPane()
{
   delete ui;
}

void SimulationSettingPane::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   this->engines.find(engine).value()->setChecked(checked);
   if (checked && this->isSliceEngine(engine)) toggle2DEngines(false);
   if (checked && this->isNonSliceEngine(engine)) toggleSliceEngines(false);
}

void SimulationSettingPane::onScalingFactorChanged(double scalingFactor)
{
   this->ui->scaleFactorSpinBox->setValue(scalingFactor);
}

void SimulationSettingPane::onRotationChanged(Rotation rotation)
{
   this->ui->xRotationDial->setValue(rotation.x());
   this->ui->yRotationDial->setValue(rotation.y());
   this->ui->zRotationDial->setValue(rotation.z());
}

void SimulationSettingPane::onAllConnectionsAreSetUp()
{
   setEnginesToDefaults();
}

void SimulationSettingPane::setUItoDefaults()
{
   ui->forceSlider->setMinimum(Settings::defaults::simulation::forceMin);
   ui->forceSlider->setMaximum(Settings::defaults::simulation::forceMax);
   ui->forceSlider->setValue(Settings::simulation().force);

   ui->stepButton->setDisabled(!Settings::simulation().frozen);

   ui->xRotationDial->setValue(Settings::canvas().rotation.x());
   ui->yRotationDial->setValue(Settings::canvas().rotation.y());
   ui->zRotationDial->setValue(Settings::canvas().rotation.z());

   ui->scaleFactorSpinBox->setValue(Settings::canvas().scalingFactor);
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

void SimulationSettingPane::setUpPrivateConnections()
{
   connect(this, SIGNAL(toggleFrozen(bool)),
            this, SLOT(onToggleFrozen(bool)));
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
           this, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
}

void SimulationSettingPane::connectToSettings()
{
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            &Settings::canvas(), SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
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

   this->engines2D.insert(Settings::engines::EnginesTypes::smoke, this->ui->smokeCheckBox);
   this->engines2D.insert(Settings::engines::EnginesTypes::glyphs, this->ui->glyphsCheckBox);
   this->engines2D.insert(Settings::engines::EnginesTypes::streamLines, this->ui->streamLinesCheckBox);
   this->engines2D.insert(Settings::engines::EnginesTypes::seedPoints, this->ui->seedPointsCheckBox);

   this->sliceEngines.insert(Settings::engines::EnginesTypes::smokeSlices, this->ui->smokeSlicesCheckBox);
   this->sliceEngines.insert(Settings::engines::EnginesTypes::glyphSlices, this->ui->glyphSlicesCheckBox);
   this->sliceEngines.insert(Settings::engines::EnginesTypes::streamLineSlices, this->ui->streamLineSlicesCheckBox);
}

void SimulationSettingPane::setFreezeButtonLabel(bool frozen)
{
   QString labelText = (frozen ? "Thaw" : "Freeze");

   this->ui->freezeButton->setText(labelText);
}

void SimulationSettingPane::toggleSliceEngines(bool toggle)
{
   emit engineToggled(Settings::engines::EnginesTypes::glyphSlices, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::smokeSlices, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::streamLineSlices, toggle);

   this->ui->viewGroupBox->setDisabled(!toggle);
}

void SimulationSettingPane::toggle2DEngines(bool toggle)
{
   emit engineToggled(Settings::engines::EnginesTypes::glyphs, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::smoke, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::streamLines, toggle);
   emit engineToggled(Settings::engines::EnginesTypes::seedPoints, toggle);

   this->ui->viewGroupBox->setDisabled(toggle);
}

bool SimulationSettingPane::isSliceEngine(Settings::engines::EnginesTypes engine)
{
   return this->sliceEngines.contains(engine);
}

bool SimulationSettingPane::isNonSliceEngine(Settings::engines::EnginesTypes engine)
{
   return this->engines2D.contains(engine);
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

void SimulationSettingPane::on_xRotationDial_valueChanged(int value)
{
   emit rotationChanged(Rotation::axis::xAxis, value);
}

void SimulationSettingPane::on_yRotationDial_valueChanged(int value)
{
   emit rotationChanged(Rotation::axis::yAxis, value);
}

void SimulationSettingPane::on_zRotationDial_valueChanged(int value)
{
   emit rotationChanged(Rotation::axis::zAxis, value);
}

void SimulationSettingPane::on_scaleFactorSpinBox_valueChanged(double value)
{
   emit scalingFactorChanged(value);
}

void SimulationSettingPane::on_resetViewButton_clicked()
{
   emit resetView();
}

void SimulationSettingPane::on_sideViewButton_pressed()
{
   emit setViewMatrixToSideView();
}

void SimulationSettingPane::on_topDownViewButton_pressed()
{
   emit setViewMatrixToTopDownView();
}
