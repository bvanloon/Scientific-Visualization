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
   registerEngines();
   setUpPrivateConnections();
   connectToSettings();
   setUItoDefaults();
}

SimulationSettingPane::~SimulationSettingPane()
{
   delete ui;
}

void SimulationSettingPane::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   EngineMap::const_iterator toggledPair = this->engines.find(engine);
   if (toggledPair != this->engines.end())
   {
      toggledPair.value()->setChecked(checked);
      if (checked && this->isSliceEngine(engine)) toggle2DEngines(false);
      if (checked && this->isNonSliceEngine(engine)) toggleSliceEngines(false);
   }
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
   for (auto engine : this->engines.keys())
   {
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
   connect(this, SIGNAL(setViewMatrixToSideView()),
           &Settings::canvas(), SLOT(onSetViewMatrixToSideView()));
   connect(this, SIGNAL(setViewMatrixToTopDownView()),
           &Settings::canvas(), SLOT(onSetViewMatrixToTopDownView()));
}

void SimulationSettingPane::registerEngines()
{
   register2DEngine(Settings::engines::EnginesTypes::smoke, this->ui->smokeCheckBox);
   register2DEngine(Settings::engines::EnginesTypes::glyphs, this->ui->glyphsCheckBox);
   register2DEngine(Settings::engines::EnginesTypes::streamLines, this->ui->streamLinesCheckBox);
   register2DEngine(Settings::engines::EnginesTypes::streamSurfaces, this->ui->streamSurfacesCheckBox);

   registerSliceEngine(Settings::engines::EnginesTypes::smokeSlices, this->ui->smokeSlicesCheckBox);
   registerSliceEngine(Settings::engines::EnginesTypes::glyphSlices, this->ui->glyphSlicesCheckBox);
   registerSliceEngine(Settings::engines::EnginesTypes::streamLineSlices, this->ui->streamLineSlicesCheckBox);
}

void SimulationSettingPane::setFreezeButtonLabel(bool frozen)
{
   QString labelText = (frozen ? "Thaw" : "Freeze");

   this->ui->freezeButton->setText(labelText);
}

void SimulationSettingPane::toggleSliceEngines(bool toggle)
{
   for (auto engine : sliceEngines.keys()) emit engineToggled(engine, toggle);
   this->ui->viewGroupBox->setDisabled(!toggle);
}

void SimulationSettingPane::toggle2DEngines(bool toggle)
{
   for (auto engine : engines2D.keys()) emit engineToggled(engine, toggle);
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

void SimulationSettingPane::register2DEngine(Settings::engines::EnginesTypes engine, QCheckBox *engineCheckBox)
{
   this->engines.insert(engine, engineCheckBox);
   this->engines2D.insert(engine, engineCheckBox);
}

void SimulationSettingPane::registerSliceEngine(Settings::engines::EnginesTypes engine, QCheckBox *engineCheckBox)
{
   this->engines.insert(engine, engineCheckBox);
   this->sliceEngines.insert(engine, engineCheckBox);
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

void SimulationSettingPane::on_streamSurfacesCheckBox_clicked(bool checked)
{
//   emit engineToggled(Settings::engines::EnginesTypes::streamSurfaces, checked);
   emit engineToggled(Settings::engines::EnginesTypes::seedCurves, checked);
   static bool warningShown = false;
   if (!warningShown++) qDebug() << "SimulationSettingPane::on_streamSurfacesCheckBox_clicked: should emit engineToggled, but this will break stuff as there is  no engine.";
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
