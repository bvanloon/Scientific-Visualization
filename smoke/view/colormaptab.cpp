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

void ColorMapTab::on_clampingCheckBox_clicked(bool checked)
{
    clampingUISetDisabled(!checked);
    emit setClamping(checked);
    emit setClampingRange(this->ui->clampingMinimumSlider->value(),
                              this->ui->clampingMaximumSlider->value());
}

void ColorMapTab::on_clampingMaximumSlider_valueChanged(float value){
    emit setClampingRange(this->ui->clampingMinimumSlider->value(), value);
}

void ColorMapTab::on_clampingMinimumSlider_valueChanged(float value)
{
    emit setClampingRange(value, this->ui->clampingMaximumSlider->value());
}

void ColorMapTab::setUItoDefaults()
{
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
    this->ui->clampingMaximumSlider->init(
                Settings::defaults::visualization::clampStart,
                Settings::defaults::visualization::clampEnd,
                Settings::defaults::visualization::clampEnd);
    this->ui->clampingMinimumSlider->init(Settings::defaults::visualization::clampStart,
                                          Settings::defaults::visualization::clampEnd,
                                          Settings::defaults::visualization::clampStart);
}

void ColorMapTab::setUpConnections()
{
    connect(this->ui->clampingMinimumSlider, SIGNAL(valueChanged(float)),
            this, SLOT(on_clampingMinimumSlider_valueChanged(float)));
    connect(this->ui->clampingMaximumSlider, SIGNAL(valueChanged(float)),
            this, SLOT(on_clampingMaximumSlider_valueChanged(float)));
}

void ColorMapTab::clampingUISetDisabled(bool disabled)
{
    this->ui->clampingMinimumLabel->setDisabled(disabled);
    this->ui->clampingMinimumSlider->setDisabled(disabled);

    this->ui->clampingMaximumLabel->setDisabled(disabled);
    this->ui->clampingMaximumSlider->setDisabled(disabled);
}
