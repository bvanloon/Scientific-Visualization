#include "slicestab.h"
#include "ui_slicestab.h"

#include "settings/visualizationsettings.h"

SlicesTab::SlicesTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::SlicesTab)
{
   ui->setupUi(this);

   connectToSettings();
   setUItoDefaults();
}

SlicesTab::~SlicesTab()
{
   delete ui;
}

void SlicesTab::connectToSettings()
{}

void SlicesTab::setUItoDefaults()
{
   this->ui->globalAlphaSpinBox->setValue(Settings::visualization::slices().globalAlpha);
   this->ui->numberOfSlicesSpinBox->setValue(Settings::visualization::slices().numberOfSlices);
}
