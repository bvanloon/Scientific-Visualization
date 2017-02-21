#include "visualizationsettingpane.h"
#include "ui_visualizationsettingspane.h"
#include "settings/settings.h"
#include "utilities.h"
#include <QDebug>

VisualizationSettingPane::VisualizationSettingPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizationSettingsPane)
{
    ui->setupUi(this);

    setUItoDefaults();
}

VisualizationSettingPane::~VisualizationSettingPane()
{
    delete ui;
}

void VisualizationSettingPane::onValueRangeChanged(float minimum, float maximum)
{
    clampingSlidersSetRange(minimum, maximum);
}

void VisualizationSettingPane::on_clampingCheckBox_clicked(bool checked)
{
    clampingUISetDisabled(!checked);
    emit setClamping(checked);
}

void VisualizationSettingPane::setUItoDefaults()
{
    this->ui->clampingMinimumSlider->setValue(Settings::defaults::visualization::clampStart);
    this->ui->clampingMaximumSlider->setValue(Settings::defaults::visualization::clampEnd);
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
    clampingSlidersSetRange(Settings::defaults::simulation::valueRangeMin,
                            Settings::defaults::simulation::valueRangeMax);
}

void VisualizationSettingPane::clampingUISetDisabled(bool disabled)
{
    this->ui->clampingMaximumSlider->setDisabled(disabled);
    this->ui->clampingMaximumLabel->setDisabled(disabled);
    this->ui->clampingMinimumSlider->setDisabled(disabled);
    this->ui->clampingMinimumLabel->setDisabled(disabled);
}

void VisualizationSettingPane::clampingSlidersSetRange(float minimum, float maximum)
{
    this->ui->clampingMinimumSlider->setRange(minimum, maximum);
    this->ui->clampingMaximumSlider->setRange(minimum, maximum);
}

void VisualizationSettingPane::on_clampingMinimumSlider_sliderMoved(int position)
{
    position = std::min(position, this->ui->clampingMaximumSlider->value());
    this->ui->clampingMinimumSlider->setValue(position);
    emit setClampingRange((float) position, (float) this->ui->clampingMaximumSlider->value());
}

void VisualizationSettingPane::on_clampingMaximumSlider_sliderMoved(int position)
{
    position = std::max(position, this->ui->clampingMinimumSlider->value());
    this->ui->clampingMaximumSlider->setValue(position);
    emit setClampingRange((float) this->ui->clampingMinimumSlider->value(), (float) position);
}
