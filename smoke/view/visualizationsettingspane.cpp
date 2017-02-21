#include "visualizationsettingspane.h"
#include "ui_visualizationsettingspane.h"

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
