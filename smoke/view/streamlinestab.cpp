#include "streamlinestab.h"
#include "ui_streamlinestab.h"

#include "settings/visualizationsettings.h"

StreamLinesTab::StreamLinesTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::StreamLinesTab)
{
   ui->setupUi(this);
   setUiToDefaults();
}

StreamLinesTab::~StreamLinesTab()
{
   delete ui;
}

ColorMapTab *StreamLinesTab::getColorMapWidget()
{
   return ui->colorMapWidget;
}

void StreamLinesTab::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   if (engine == Settings::engines::EnginesTypes::seedPoints)
   {
      this->ui->showSeedPoinsCheckBox->setChecked(checked);
   }
}

void StreamLinesTab::setUiToDefaults()
{
   this->ui->colorMapWidget->getVariableSelector()->setCurrentIndex(Settings::visualization::streamLines().colorMap->scalar);
   this->ui->colorMapWidget->getVariableSelector()->setDisabled(true);

   this->ui->timeStepSelector->setValue(Settings::visualization::streamLines().timeStep);
   qDebug() << "Set selectors to correct default values";

   this->ui->showSeedPoinsCheckBox->setChecked(Settings::defaults::engines::activeEngines[Settings::engines::EnginesTypes::seedPoints]);
}

void StreamLinesTab::on_timeStepSelector_valueChanged(double value)
{
   emit timeStepChanged(value);
}

void StreamLinesTab::on_clearSeedPointsButton_clicked()
{
   emit clearSeedPoints();
}

void StreamLinesTab::on_showSeedPoinsCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::seedPoints, checked);

   if (checked) emit engineToggled(Settings::engines::EnginesTypes::streamLines, true);
}
