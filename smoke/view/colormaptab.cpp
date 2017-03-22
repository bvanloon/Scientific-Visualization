#include "colormaptab.h"
#include "ui_colormaptab.h"
#include "settings/settings.h"
#include "settings/simulationsettings.h"
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

void ColorMapTab::connectToColorMapSettings(Settings::visualization::ColorMap *colorMap)
{
   connect(this, SIGNAL(textureVariableChanged(Settings::sim::Scalar)),
            colorMap, SLOT(onTextureVariableChanged(Settings::sim::Scalar)));
   connect(colorMap, SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
           this, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
}

void ColorMapTab::on_clampingCheckBox_clicked(bool checked)
{
   clampingUISetDisabled(!checked);
   emit setClamping(checked);
   float minimum = checked ? this->ui->clampingMinimumFloatBox->value() : 0.0f;
   float maximum = checked ? this->ui->clampingMaximumFloatBox->value() : 1.0f;
   emit setClampingRange(minimum, maximum);
}

void ColorMapTab::on_numColorsSlider_valueChanged(int value)
{
   AbstractColorMap *newColormap = ColorMapFactory::get()->createColorMap(
                static_cast<ColorMapFactory::colorMaps>(this->ui->colormapSelector->currentIndex()),
                value,
                this->ui->saturationSlider->value());
   emit colorMapChanged(*newColormap);
}

void ColorMapTab::setUItoDefaults()
{
   this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::colormap::clampingOn);
   clampingUISetDisabled(!Settings::defaults::visualization::colormap::clampingOn);

   this->ui->clampingMaximumFloatBox->setMinimum(Settings::defaults::visualization::colormap::clampMin);
   this->ui->clampingMaximumFloatBox->setMaximum(Settings::defaults::visualization::colormap::clampMax);
   this->ui->clampingMaximumFloatBox->setValue(Settings::defaults::visualization::colormap::clampMax);

   this->ui->clampingMinimumFloatBox->setMinimum(Settings::defaults::visualization::colormap::clampMin);
   this->ui->clampingMinimumFloatBox->setMaximum(Settings::defaults::visualization::colormap::clampMax);
   this->ui->clampingMinimumFloatBox->setValue(Settings::defaults::visualization::colormap::clampMin);

   this->ui->colormapSelector->addItems(ColorMapFactory::getColorMapNames());
   this->ui->colormapSelector->setCurrentIndex(Settings::defaults::visualization::colormap::colormap);

   this->ui->numColorsSlider->setMinimum(Settings::defaults::visualization::colormap::minNumColors);
   this->ui->numColorsSlider->setMaximum(Settings::defaults::visualization::colormap::maxNumColors);
   this->ui->numColorsSlider->setValue(Settings::defaults::visualization::colormap::numColors);

   this->ui->saturationSlider->setMinimum(Settings::defaults::visualization::colormap::minSaturation);
   this->ui->saturationSlider->setMaximum(Settings::defaults::visualization::colormap::maxSaturation);
   this->ui->saturationSlider->setValue(Settings::defaults::visualization::colormap::saturation);

   this->ui->variableSelector->addItems(Settings::visualization::getScalarVariableNames());
   this->ui->variableSelector->setCurrentIndex(Settings::defaults::visualization::colormap::scalar);
}

void ColorMapTab::setUpConnections()
{
   connect(this->ui->numColorsSlider, SIGNAL(valueChanged(int)),
            this, SLOT(on_numColorsSlider_valueChanged(int)));

   connect(this, SIGNAL(setClampingRange(float,float)),
            this->ui->colormapLegend, SLOT(onClampRangeChanged(float,float)));

   connect(this, SIGNAL(colorMapChanged(AbstractColorMap)),
            this->ui->colormapLegend, SLOT(onColorMapChanged(AbstractColorMap)));

   connect(this, SIGNAL(valueRangeChanged(float,float)),
            this->ui->colormapLegend, SLOT(onValueRangeChanged(float,float)));

   connect(&Settings::simulation(), SIGNAL(valueRangeChanged(Settings::sim::Scalar,float,float)),
            this, SLOT(onValueRangeChanged(Settings::sim::Scalar,float,float)));
}

void ColorMapTab::clampingUISetDisabled(bool disabled)
{
   this->ui->clampingMinimumLabel->setDisabled(disabled);
   this->ui->clampingMinimumFloatBox->setDisabled(disabled);

   this->ui->clampingMaximumLabel->setDisabled(disabled);
   this->ui->clampingMaximumFloatBox->setDisabled(disabled);
}

void ColorMapTab::on_colormapSelector_currentIndexChanged(int index)
{
   AbstractColorMap *newColormap = ColorMapFactory::get()->createColorMap(
                static_cast<ColorMapFactory::colorMaps>(index),
                ui->numColorsSlider->value(),
                ui->saturationSlider->value(), 0.5f);
   emit colorMapChanged(*newColormap);
}

void ColorMapTab::on_variableSelector_currentIndexChanged(int index)
{
   emit textureVariableChanged(
      static_cast<Settings::sim::Scalar>(index));
}

void ColorMapTab::onValueRangeChanged(Settings::sim::Scalar variable, float min, float max)
{
   if (colormapSettings->scalar == variable) emit valueRangeChanged(min, max);
}

void ColorMapTab::on_colorPickerButton_clicked()
{
   QColor color = QColorDialog::getColor(Qt::green, this, "Choose Hue for Hue Color Map", QColorDialog::DontUseNativeDialog);

   if (color.isValid())
   {
      double h, s, v;
      qreal a;
      color.getHsvF(&h, &s, &v, &a);
      AbstractColorMap *newColormap = ColorMapFactory::get()->createColorMap(
                    static_cast<ColorMapFactory::colorMaps>(this->ui->colormapSelector->currentIndex()),
                    ui->numColorsSlider->value(),
                    ui->saturationSlider->value(), h);


      emit colorMapChanged(*newColormap);
   }
}

void ColorMapTab::setColormapSettings(Settings::visualization::ColorMap *value)
{
   colormapSettings = value;
   connectToColorMapSettings(value);
}

QComboBox *ColorMapTab::getVariableSelector() const
{
   return ui->variableSelector;
}

void ColorMapTab::on_clampingMinimumFloatBox_valueChanged(double value)
{
   double maximum = this->ui->clampingMaximumFloatBox->value();
   double minimum = qMin(value, maximum - Settings::defaults::visualization::colormap::clampEpsilon);

   this->ui->clampingMinimumFloatBox->setValue(minimum);
   emit setClampingRange(minimum, maximum);
}

void ColorMapTab::on_clampingMaximumFloatBox_valueChanged(double value)
{
   double minimum = this->ui->clampingMinimumFloatBox->value();
   double maximum = qMax(value, minimum + Settings::defaults::visualization::colormap::clampEpsilon);

   this->ui->clampingMaximumFloatBox->setValue(maximum);
   emit setClampingRange(minimum, maximum);
}

void ColorMapTab::on_saturationSlider_valueChanged(double value)
{
   this->ui->saturationSlider->setValue(value);
   AbstractColorMap *newColormap = ColorMapFactory::get()->createColorMap(
                 static_cast<ColorMapFactory::colorMaps>(this->ui->colormapSelector->currentIndex()),
                 this->ui->numColorsSlider->value(),
                 value, 0.5f);

   emit colorMapChanged(*newColormap);
}
