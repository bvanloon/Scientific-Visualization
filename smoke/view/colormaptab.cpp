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
    float minimum = checked ? this->ui->clampingMinimumSlider->value() : 0.0f;
    float maximum = checked ? this->ui->clampingMaximumSlider->value() : 1.0f;
    emit setClampingRange(minimum, maximum);
}

void ColorMapTab::on_clampingMaximumSlider_valueChanged(float value){
    float minimum = this->ui->clampingMinimumSlider->value();
    float maximum = qMax(value, minimum + Settings::defaults::visualization::colormap::clampEpsilon);
    this->ui->clampingMaximumSlider->setValue(maximum);
    emit setClampingRange(minimum, maximum);
}

void ColorMapTab::on_clampingMinimumSlider_valueChanged(float value)
{
    float maximum = this->ui->clampingMaximumSlider->value();
    float minimum = qMin(value, maximum + Settings::defaults::visualization::colormap::clampEpsilon);
    this->ui->clampingMinimumSlider->setValue(minimum);
    emit setClampingRange(minimum, maximum);

}


void ColorMapTab::on_saturationSlider_valueChanged(float value)
{
    this->ui->saturationSlider->setValue(value);
    AbstractColorMap* newColormap = ColorMapFactory::get()->createColorMap(
                static_cast<ColorMapFactory::colorMaps>(this->ui->colormapSelector->currentIndex()),
                this->ui->numColorsSlider->value(),
                value);

    emit colorMapChanged(*newColormap);
}

void ColorMapTab::on_numColorsSlider_valueChanged(int value)
{
    AbstractColorMap* newColormap = ColorMapFactory::get()->createColorMap(
                static_cast<ColorMapFactory::colorMaps>(this->ui->colormapSelector->currentIndex()),
                value,
                this->ui->saturationSlider->value());
    emit colorMapChanged(*newColormap);
}

void ColorMapTab::setUItoDefaults()
{
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::colormap::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::colormap::clampingOn);
    this->ui->clampingMaximumSlider->init(
                Settings::defaults::visualization::colormap::clampMin,
                Settings::defaults::visualization::colormap::clampMax,
                Settings::defaults::visualization::colormap::clampMax);
    this->ui->clampingMinimumSlider->init(
                Settings::defaults::visualization::colormap::clampMin,
                Settings::defaults::visualization::colormap::clampMax,
                Settings::defaults::visualization::colormap::clampMin);
    this->ui->numColorsSlider->init(
                Settings::defaults::visualization::colormap::minNumColors,
                Settings::defaults::visualization::colormap::maxNumColors,
                Settings::defaults::visualization::colormap::numColors);
    this->ui->saturationSlider->init(
                Settings::defaults::visualization::colormap::minSaturation,
                Settings::defaults::visualization::colormap::maxSaturation,
                Settings::defaults::visualization::colormap::saturation);

    this->ui->colormapSelector->addItems(ColorMapFactory::getColorMapNames());
}

void ColorMapTab::setUpConnections()
{
    connect(this->ui->clampingMinimumSlider, SIGNAL(valueChanged(float)),
            this, SLOT(on_clampingMinimumSlider_valueChanged(float)));
    connect(this->ui->clampingMaximumSlider, SIGNAL(valueChanged(float)),
            this, SLOT(on_clampingMaximumSlider_valueChanged(float)));
    connect(this->ui->numColorsSlider, SIGNAL(valueChanged(int)),
            this, SLOT(on_numColorsSlider_valueChanged(int)));
    connect(this->ui->saturationSlider, SIGNAL(valueChanged(float)),
            this, SLOT(on_saturationSlider_valueChanged(float)));
}

void ColorMapTab::clampingUISetDisabled(bool disabled)
{
    this->ui->clampingMinimumLabel->setDisabled(disabled);
    this->ui->clampingMinimumSlider->setDisabled(disabled);

    this->ui->clampingMaximumLabel->setDisabled(disabled);
    this->ui->clampingMaximumSlider->setDisabled(disabled);
}

void ColorMapTab::on_colormapSelector_currentIndexChanged(int index)
{
    AbstractColorMap* newColormap = ColorMapFactory::get()->createColorMap(
                static_cast<ColorMapFactory::colorMaps>(index),
                ui->numColorsSlider->value(),
                ui->saturationSlider->value());
    emit colorMapChanged(*newColormap);
}
