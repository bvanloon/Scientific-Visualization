#include "visualizationsettingspane.h"
#include "ui_visualizationsettingspane.h"
#include "settings/settings.h"
#include <QDebug>

VisualizationSettingsPane::VisualizationSettingsPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizationSettingsPane)
{
    ui->setupUi(this);

    setUItoDefaults();
}

VisualizationSettingsPane::~VisualizationSettingsPane()
{
    delete ui;
}

void VisualizationSettingsPane::on_clampingCheckBox_clicked(bool checked)
{
    emit setClamping(checked);
}

void VisualizationSettingsPane::setUItoDefaults()
{
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
}
