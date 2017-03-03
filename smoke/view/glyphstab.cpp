#include "glyphstab.h"
#include "ui_glyphstab.h"

GlyphsTab::GlyphsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlyphsTab)
{
    ui->setupUi(this);
}

GlyphsTab::~GlyphsTab()
{
    delete ui;
}

ColorMapTab *GlyphsTab::getColorMapWidget()
{
    return ui->colorMapGlyphs;
}
