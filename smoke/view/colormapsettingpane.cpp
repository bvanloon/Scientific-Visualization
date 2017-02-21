#include "colormapsettingpane.h"
#include "ui_visualizationsettingspane.h"
#include "settings/settings.h"
#include "utilities.h"
#include <QDebug>

ColorMapSettingPane::ColorMapSettingPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapSettingPane)
{
    ui->setupUi(this);

    setUItoDefaults();
}

ColorMapSettingPane::~ColorMapSettingPane()
{
    delete ui;
}

void ColorMapSettingPane::onValueRangeChanged(float minimum, float maximum)
{
    clampingSlidersSetRange(minimum, maximum);
}

void ColorMapSettingPane::on_clampingCheckBox_clicked(bool checked)
{
    clampingUISetDisabled(!checked);
    emit setClamping(checked);
}

void ColorMapSettingPane::setUItoDefaults()
{
    this->ui->clampingMinimumSlider->setValue(Settings::defaults::visualization::clampStart);
    this->ui->clampingMaximumSlider->setValue(Settings::defaults::visualization::clampEnd);
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
    clampingSlidersSetRange(Settings::defaults::simulation::valueRangeMin,
                            Settings::defaults::simulation::valueRangeMax);
}

void ColorMapSettingPane::clampingUISetDisabled(bool disabled)
{
    this->ui->clampingMaximumSlider->setDisabled(disabled);
    this->ui->clampingMaximumLabel->setDisabled(disabled);
    this->ui->clampingMinimumSlider->setDisabled(disabled);
    this->ui->clampingMinimumLabel->setDisabled(disabled);
}

void ColorMapSettingPane::clampingSlidersSetRange(float minimum, float maximum)
{
    this->ui->clampingMinimumSlider->setRange(minimum, maximum);
    this->ui->clampingMaximumSlider->setRange(minimum, maximum);
}

void ColorMapSettingPane::on_clampingMinimumSlider_sliderMoved(int position)
{
    position = std::min(position, this->ui->clampingMaximumSlider->value());
    this->ui->clampingMinimumSlider->setValue(position);
    emit setClampingRange((float) position, (float) this->ui->clampingMaximumSlider->value());
}

void ColorMapSettingPane::on_clampingMaximumSlider_sliderMoved(int position)
{
    position = std::max(position, this->ui->clampingMinimumSlider->value());
    this->ui->clampingMaximumSlider->setValue(position);
    emit setClampingRange((float) this->ui->clampingMinimumSlider->value(), (float) position);
}
