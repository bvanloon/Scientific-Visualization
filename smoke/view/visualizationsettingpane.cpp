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
}
