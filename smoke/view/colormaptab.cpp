#include "colormaptab.h"
#include "ui_colormaptab.h"
#include "settings/settings.h"
#include <QDebug>

ColorMapTab::ColorMapTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapTab)
{
    ui->setupUi(this);

    setUItoDefaults();
    setUpConnections();
}

ColorMapTab::~ColorMapTab()
{
    delete ui;
}

void ColorMapTab::onValueRangeChanged(float minimum, float maximum)
{
    qDebug() << "ColorMapTab::onValueRangeChanged: do something, possibly set the range of the sliders.";
}

void ColorMapTab::on_clampingCheckBox_clicked(bool checked)
{
    clampingUISetDisabled(!checked);
    emit setClamping(checked);
    qDebug() << "ColorMapTab::on_clampingCheckBox_clicked: emit the clamping range.";
}

void ColorMapTab::on_clampingMaximumSlider_valueChanged(float value){
    qDebug() << "ColorMapTab::on_clampingMaximumSlider_valueChanged " << value;
}


void ColorMapTab::setUItoDefaults()
{
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
    this->ui->clampingMaximumSlider->init(
                Settings::defaults::visualization::clampStart,
                Settings::defaults::visualization::clampEnd,
                Settings::defaults::visualization::clampEnd);
    qDebug() << "ColorMapTab::setUItoDefaults(): Set the sliders to the correct values.";
}

void ColorMapTab::setUpConnections()
{
    connect(this->ui->clampingMaximumSlider, SIGNAL(valueChanged(float)),
            this, SLOT(on_clampingMaximumSlider_valueChanged(float)));
}

void ColorMapTab::clampingUISetDisabled(bool disabled)
{
    qDebug() << "ColorMapTab::clampingUISetDisabled: Disable the sliders";
}
