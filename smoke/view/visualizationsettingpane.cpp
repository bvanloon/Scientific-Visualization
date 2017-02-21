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

void VisualizationSettingPane::on_clampingCheckBox_clicked(bool checked)
{
    clampingUISetDisabled(!checked);
    emit setClamping(checked);
}

void VisualizationSettingPane::setUItoDefaults()
{
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    this->ui->clampingMinimumSlider->setValue(
                mapToRange(
                    Settings::defaults::visualization::clampStart,
                    0.0f,
                    1.0f,
                    (float) this->ui->clampingMinimumSlider->minimum(),
                    (float) this->ui->clampingMinimumSlider->maximum()));
    this->ui->clampingMaximumSlider->setValue(
                mapToRange(
                    Settings::defaults::visualization::clampEnd,
                    0.0f,
                    1.0f,
                    (float) this->ui->clampingMaximumSlider->minimum(),
                    (float) this->ui->clampingMaximumSlider->maximum()));
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
}

void VisualizationSettingPane::clampingUISetDisabled(bool disabled)
{
    this->ui->clampingMaximumSlider->setDisabled(disabled);
    this->ui->clampingMaximumLabel->setDisabled(disabled);
    this->ui->clampingMinimumSlider->setDisabled(disabled);
    this->ui->clampingMinimumLabel->setDisabled(disabled);
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
