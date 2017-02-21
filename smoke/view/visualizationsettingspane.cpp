#include "visualizationsettingspane.h"
#include "ui_visualizationsettingspane.h"
#include <QDebug>

VisualizationSettingsPane::VisualizationSettingsPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizationSettingsPane)
{
    ui->setupUi(this);
}

VisualizationSettingsPane::~VisualizationSettingsPane()
{
    delete ui;
}

void VisualizationSettingsPane::on_clampingCheckBox_clicked(bool checked)
{
    emit setClamping(checked);
}

