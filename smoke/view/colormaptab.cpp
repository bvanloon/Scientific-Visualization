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


void ColorMapTab::setUItoDefaults()
{
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
    qDebug() << "ColorMapTab::setUItoDefaults(): Set the sliders to the correct values.";
}

void ColorMapTab::clampingUISetDisabled(bool disabled)
{
    qDebug() << "ColorMapTab::clampingUISetDisabled: Disable the sliders";
}
