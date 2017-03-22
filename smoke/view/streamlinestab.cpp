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

void StreamLinesTab::setUiToDefaults()
{
   this->ui->colorMapWidget->getVariableSelector()->setCurrentIndex(Settings::sim::Scalar::fluidVelocityMagnitude);
   this->ui->colorMapWidget->getVariableSelector()->setDisabled(true);
}
