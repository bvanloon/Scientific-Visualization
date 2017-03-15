#include "settings/visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   vectorScale(1000)
{
   vectorGetter = Vertex::getVectorGetter(Settings::defaults::visualization::glyphs::vector);
   this->drawMode = Settings::defaults::visualization::glyphs::defaultDrawMode;
}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

void Settings::visualization::Glyphs::onVectorFieldChanged(Settings::sim::Vector vectorField)
{
   vectorGetter = Vertex::getVectorGetter(vectorField);
}

void Settings::visualization::Glyphs::onGlyphChanged(Settings::sim::GlyphsType glyph)
{
   this->glyph = glyph;
   this->drawMode = Settings::sim::drawModes.at(glyph);
}
