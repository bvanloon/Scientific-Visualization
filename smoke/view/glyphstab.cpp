#include "glyphstab.h"
#include "ui_glyphstab.h"

GlyphsTab::GlyphsTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::GlyphsTab)
{
   ui->setupUi(this);
   setUiToDefaults();
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
   ui->gridHeightSpinBox->setValue(Settings::defaults::visualization::glyphs::gridSize.height());
   ui->gridWidthSpinBox->setValue(Settings::defaults::visualization::glyphs::gridSize.width());

   ui->vectorFieldComboBox->addItems(Settings::visualization::getVectorVariableNames());
   ui->vectorFieldComboBox->setCurrentIndex(Settings::defaults::visualization::glyphs::vector);

   //Temporary, until we have support for a rectalinear grid.
   ui->gridHeightSpinBox->setValue(Settings::defaults::visualization::glyphs::gridSize.width());
   ui->gridHeightSpinBox->setDisabled(true);

   ui->glyphSelector->addItems(GlyphsFactory::getGlyphsNames());
   ui->glyphSelector->setCurrentIndex(Settings::defaults::visualization::glyphs::defaultGlyph);
}

void GlyphsTab::setUpConnections()
{}

void GlyphsTab::on_gridHeightSpinBox_valueChanged(int height)
{
   int width = ui->gridWidthSpinBox->value();
   emit gridDimensionChanged(width, height);
}

void GlyphsTab::on_gridWidthSpinBox_valueChanged(int width)
{
   //Temporary, until we have support for a rectalinear grid.
   ui->gridHeightSpinBox->setValue(width);

   int height = ui->gridHeightSpinBox->value();
   emit gridDimensionChanged(width, height);
}

void GlyphsTab::on_vectorFieldComboBox_currentIndexChanged(int index)
{
   emit vectorFieldChanged(static_cast<Settings::sim::Vector>(index));
}

void GlyphsTab::on_glyphSelector_currentIndexChanged(int index)
{
   emit glyphChanged(static_cast<Settings::sim::GlyphsType>(index));
}
