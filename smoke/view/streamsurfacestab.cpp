#include "streamsurfacestab.h"
#include "ui_streamsurfacestab.h"

#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

StreamSurfacesTab::StreamSurfacesTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::StreamSurfacesTab)
{
   ui->setupUi(this);
   connectToSettings();
   fillUI();
   setUiToDefaults();
}

StreamSurfacesTab::~StreamSurfacesTab()
{
   delete ui;
}

ColorMapTab *StreamSurfacesTab::getColorMapWidget()
{
   return ui->colorMapWidget;
}

void StreamSurfacesTab::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   if (engine == Settings::engines::EnginesTypes::seedCurves) this->ui->showSeedCurvesCheckBox->setChecked(checked);
}

void StreamSurfacesTab::onVectoFieldChanged(Settings::sim::Vector vectorField, Settings::sim::Scalar magnitude)
{
   this->ui->colorMapWidget->getVariableSelector()->setCurrentIndex(magnitude);
   this->ui->vectorFieldComboBox->setCurrentIndex(vectorField);
}

void StreamSurfacesTab::on_clearSeedCurvesButton_pressed()
{
   emit clearSeedCurves();
}

void StreamSurfacesTab::on_showSeedCurvesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::seedCurves, checked);
   if (checked) emit engineToggled(Settings::engines::EnginesTypes::streamSurfaces, true);
}

void StreamSurfacesTab::setUiToDefaults()
{
   this->ui->showSeedCurvesCheckBox->setChecked(Settings::defaults::engines::activeEngines[Settings::engines::EnginesTypes::seedCurves]);
   this->ui->showLinesCheckBox->setChecked(Settings::visualization::streakSurface().showLines);
   this->ui->showSurfaceCheckBox->setChecked(Settings::visualization::streakSurface().showSurface);
   this->ui->showVerticesCheckBox->setChecked(Settings::visualization::streakSurface().showVertices);
   this->ui->resolutionSpinBox->setValue(Settings::visualization::streakSurface().resolution);
   this->ui->numStatesSpinBox->setValue(Settings::visualization::streakSurface().getNumberOfStates());
   this->ui->vectorFieldComboBox->setCurrentIndex(Settings::visualization::streakSurface().vectorField);
   this->ui->colorMapWidget->getVariableSelector()->setCurrentIndex(Settings::visualization::streakSurface().vectorFieldMagnitude);
   this->ui->colorMapWidget->getVariableSelector()->setDisabled(true);
}

void StreamSurfacesTab::connectToSettings()
{
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            &Settings::canvas(), SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
   connect(&Settings::canvas(), SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            this, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
   connect(this, SIGNAL(clearSeedCurves()),
           &Settings::visualization::streakSurface(), SLOT(onClearSeedCurves()));
   connect(this, SIGNAL(resolutionChanged(int)),
           &Settings::visualization::streakSurface(), SLOT(onResolutionChanged(int)));
   connect(this, SIGNAL(showStreamSurfaceLinesToggled(bool)),
           &Settings::visualization::streakSurface(), SLOT(onShowStreamSurfaceLinesToggled(bool)));
   connect(this, SIGNAL(showStreamSurfaceVerticesToggled(bool)),
           &Settings::visualization::streakSurface(), SLOT(onShowStreamSurfaceVerticesToggled(bool)));
   connect(this, SIGNAL(numberOfStatesChanged(int)),
           &Settings::visualization::streakSurface(), SLOT(onNumberOfStatesChanged(int)));
   connect(this, SIGNAL(showStreamSurfaceFaceToggled(bool)),
           &Settings::visualization::streakSurface(), SLOT(onShowStreamSurfaceFaceToggled(bool)));
   connect(this, SIGNAL(vectorFieldChanged(Settings::sim::Vector)),
           &Settings::visualization::streakSurface(), SLOT(onVectorFieldChanged(Settings::sim::Vector)));
   connect(&Settings::visualization::streakSurface(), SIGNAL(vectorFieldChanged(Settings::sim::Vector,Settings::sim::Scalar)),
           this, SLOT(onVectoFieldChanged(Settings::sim::Vector,Settings::sim::Scalar)));
}

void StreamSurfacesTab::on_resolutionSpinBox_valueChanged(int value)
{
   emit resolutionChanged(value);
}

void StreamSurfacesTab::on_showLinesCheckBox_clicked(bool checked)
{
   emit showStreamSurfaceLinesToggled(checked);
}

void StreamSurfacesTab::on_showVerticesCheckBox_clicked(bool checked)
{
   emit showStreamSurfaceVerticesToggled(checked);
}

void StreamSurfacesTab::on_showSurfaceCheckBox_clicked(bool checked)
{
   emit showStreamSurfaceFaceToggled(checked);
}

void StreamSurfacesTab::fillUI()
{
   this->ui->vectorFieldComboBox->addItems(Settings::visualization::getNonDerivedVectorVariableNames());
}

void StreamSurfacesTab::on_numStatesSpinBox_valueChanged(int value)
{
   emit numberOfStatesChanged(value);
}

void StreamSurfacesTab::on_vectorFieldComboBox_currentIndexChanged(int index)
{
   emit vectorFieldChanged(static_cast<Settings::sim::Vector>(index));
}
