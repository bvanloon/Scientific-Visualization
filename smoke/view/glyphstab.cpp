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
    ui->gridHeightSpinBox->setValue(Settings::visualization().gridSize.height());
    ui->gridWidthSpinBox->setValue(Settings::visualization().gridSize.width());
}

void GlyphsTab::setUpConnections()
{

}
