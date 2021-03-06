#include "slicestab.h"
#include "ui_slicestab.h"

SlicesTab::SlicesTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::SlicesTab)
{
   ui->setupUi(this);

   connectToSettings();

   initializeUI();

   setUItoDefaults();
}

SlicesTab::~SlicesTab()
{
   delete ui;
}

void SlicesTab::connectToSettings()
{
   connect(this, SIGNAL(numberOfSlicesChanged(int)),
            &Settings::visualization::slices(), SLOT(onNumberOfSlicesChanged(int)));
   connect(this, SIGNAL(globalAlphaChanged(double)),
            &Settings::visualization::slices(), SLOT(onGlobalAlphaChanged(double)));
   connect(this, SIGNAL(numberOfStatesPerSliceChanged(int)),
           &Settings::visualization::slices(), SLOT(onNumberOfStatesPerSliceChanged(int)));
   connect(this, SIGNAL(combinationMethodChanged(Settings::visualization::Slices::CombinationMethod)),
           &Settings::visualization::slices(), SLOT(onCombinationMethodChanged(Settings::visualization::Slices::CombinationMethod)));
}

void SlicesTab::initializeUI()
{
   this->ui->combinationmethodComboBox->addItems(Settings::visualization::slices().getCombinationMethodNames());
}

void SlicesTab::setUItoDefaults()
{
   this->ui->globalAlphaSpinBox->setValue(Settings::visualization::slices().globalAlpha);
   this->ui->numberOfSlicesSpinBox->setValue(Settings::visualization::slices().numSlices);
   this->ui->numberOfStatesSpinBox->setValue(Settings::visualization::slices().numStatesPerSlice);
   this->ui->combinationmethodComboBox->setCurrentIndex(Settings::defaults::visualization::slices::combinationMethod);
}

void SlicesTab::on_globalAlphaSpinBox_valueChanged(double value)
{
   emit globalAlphaChanged(value);
}

void SlicesTab::on_numberOfSlicesSpinBox_valueChanged(int value)
{
   emit numberOfSlicesChanged(value);
}

void SlicesTab::on_numberOfStatesSpinBox_valueChanged(int value)
{
   emit numberOfStatesPerSliceChanged(value);
}

void SlicesTab::on_combinationmethodComboBox_currentIndexChanged(int index)
{
   emit combinationMethodChanged(static_cast<Settings::visualization::Slices::CombinationMethod>(index));
}
