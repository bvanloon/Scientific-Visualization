#include "visualizationsettingpane.h"
#include "ui_visualizationsettingspane.h"
#include "settings/settings.h"
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
}
