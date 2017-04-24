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

void StreamSurfacesTab::onVectoFieldChanged(Settings::sim::Vector vectorField, Settings::sim::Scalar magnitude)
{
   this->ui->colorMapWidget->getVariableSelector()->setCurrentIndex(magnitude);
   this->ui->vectorFieldComboBox->setCurrentIndex(vectorField);
}

void StreamSurfacesTab::on_clearSeedCurvesButton_pressed()
{
   emit clearSeedCurves();
}

void StreamSurfacesTab::setUiToDefaults()
{
   this->ui->showLinesCheckBox->setChecked(Settings::visualization::streakSurface().showLines);
   this->ui->showSurfaceCheckBox->setChecked(Settings::visualization::streakSurface().showSurface);
   this->ui->showVerticesCheckBox->setChecked(Settings::visualization::streakSurface().showVertices);
   this->ui->resolutionSpinBox->setValue(Settings::visualization::streakSurface().resolution);
   this->ui->numStatesSpinBox->setValue(Settings::visualization::streakSurface().numberOfStates);
   this->ui->vectorFieldComboBox->setCurrentIndex(Settings::visualization::streakSurface().vectorField);
   this->ui->colorMapWidget->getVariableSelector()->setCurrentIndex(Settings::visualization::streakSurface().vectorFieldMagnitude);
   this->ui->colorMapWidget->getVariableSelector()->setDisabled(true);
   this->ui->divergenceSensitivitySpinBox->setValue(Settings::visualization::streakSurface().divergenceSensitivity);
}

void StreamSurfacesTab::connectToSettings()
{
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            &Settings::canvas(), SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
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
   connect(this, SIGNAL(divergenceSensitivityChanged(double)),
           &Settings::visualization::streakSurface(), SLOT(onDivergenceSensitivityChanged(double)));
   connect(this, SIGNAL(toggleAllEngines(bool)),
           &Settings::canvas(), SLOT(onToggleAllEngines(bool)));
   connect(this, SIGNAL(toggleAll3Dengines(bool)),
           &Settings::canvas(), SLOT(onToggleAll3DEngines(bool)));
   connect(this, SIGNAL(toggleListenForVertices(bool)),
           &Settings::visualization::streakSurface(), SLOT(onToggleListenForVertices(bool)));
   connect(this, SIGNAL(removeLastVertexFromSeedCurve()),
           &Settings::visualization::streakSurface(), SLOT(onRemoveLastVertexFromSeedCurve()));
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

void StreamSurfacesTab::on_divergenceSensitivitySpinBox_valueChanged(double value)
{
   emit divergenceSensitivityChanged(value);
}

void StreamSurfacesTab::on_defineSeedCurveButton_clicked()
{
   static bool drawingSeedCurve = false;
   drawingSeedCurve = !drawingSeedCurve;
   if (drawingSeedCurve) enterDefineSeedCurveMode();
   else exitDefineSeedCurveMode();
}

void StreamSurfacesTab::enterDefineSeedCurveMode()
{
   emit toggleAll3Dengines(false);
   emit engineToggled(Settings::engines::seedCurve, true);
   emit toggleListenForVertices(true);
   this->ui->defineSeedCurveButton->setText("Show Stream Objects");
}

void StreamSurfacesTab::exitDefineSeedCurveMode()
{
   emit toggleListenForVertices(false);
   emit engineToggled(Settings::engines::seedCurve, false);
   emit toggleAllEngines(false);
   emit engineToggled(Settings::engines::streakObjects, true);
   this->ui->defineSeedCurveButton->setText("Define");
}

void StreamSurfacesTab::on_clearLastVertexButton_clicked()
{
   emit removeLastVertexFromSeedCurve();
}
