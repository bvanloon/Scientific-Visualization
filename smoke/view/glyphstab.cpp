#include "glyphstab.h"
#include "ui_glyphstab.h"

GlyphsTab::GlyphsTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::GlyphsTab)
{
   ui->setupUi(this);
   setUiToDefaults();
   connectToSettings();
}

GlyphsTab::~GlyphsTab()
{
   delete ui;
}

ColorMapTab *GlyphsTab::getColorMapWidget()
{
   return ui->colorMapGlyphs;
}

void GlyphsTab::setUiToDefaults()
{
   ui->gridHeightSpinBox->setValue(Settings::visualization::glyphs().gridDimension.height());
   ui->gridWidthSpinBox->setValue(Settings::visualization::glyphs().gridDimension.width());

   ui->vectorFieldComboBox->addItems(Settings::visualization::getAllVectorVariableNames());
   ui->vectorFieldComboBox->setCurrentIndex(Settings::visualization::glyphs().vectorField);

   ui->scale->setValue(Settings::visualization::glyphs().scale);
   updateScaleSpinBoxConfiguration(Settings::visualization::glyphs().scale);

   ui->glyphSelector->addItems(Settings::visualization::getGlyphNames());
   ui->glyphSelector->setCurrentIndex(Settings::visualization::glyphs().glyph);

   ui->jitterFactorSpinBox->setValue(Settings::visualization::glyphs().jitterFactor);

   //Temporary, until we have support for a rectalinear grid.
   ui->gridHeightSpinBox->setValue(ui->gridWidthSpinBox->value());
   ui->gridHeightSpinBox->setDisabled(true);
}

void GlyphsTab::connectToSettings()
{
   connect(this, SIGNAL(gridDimensionChanged(QSizeF)),
            &Settings::visualization::glyphs(), SLOT(onGridDimensionChanged(QSizeF)));
   connect(this, SIGNAL(jitterFactorChanged(double)),
           &Settings::visualization::glyphs(), SLOT(onJitterFactorChanged(double)));
}

void GlyphsTab::updateScaleSpinBoxConfiguration(double currentValue)
{
   if (currentValue <= 1.0)
   {
      ui->scale->setDecimals(2);
      ui->scale->setSingleStep(0.1);
   }
   else
   {
      ui->scale->setDecimals(0);
      ui->scale->setSingleStep(1);
   }
}

void GlyphsTab::on_gridHeightSpinBox_valueChanged(int height)
{
   int width = ui->gridWidthSpinBox->value();
   QSizeF newSize(width, height);

   emit gridDimensionChanged(newSize.width(), newSize.height());
   emit gridDimensionChanged(newSize);
}

void GlyphsTab::on_gridWidthSpinBox_valueChanged(int width)
{
   //Temporary, until we have support for a rectalinear grid.
   ui->gridHeightSpinBox->setValue(width);

   int height = ui->gridHeightSpinBox->value();
   QSizeF newSize(width, height);

   emit gridDimensionChanged(newSize.width(), newSize.height());
   emit gridDimensionChanged(newSize);
}

void GlyphsTab::on_vectorFieldComboBox_currentIndexChanged(int index)
{
   emit vectorFieldChanged(static_cast<Settings::sim::Vector>(index));
}

void GlyphsTab::on_glyphSelector_currentIndexChanged(int index)
{
   emit glyphChanged(static_cast<Settings::sim::GlyphsType>(index));
}

void GlyphsTab::on_scale_valueChanged(double scale)
{
   updateScaleSpinBoxConfiguration(scale);
   emit scaleChanged(scale);
}

void GlyphsTab::on_jitterFactorSpinBox_valueChanged(double value)
{
   emit jitterFactorChanged(value);
}
