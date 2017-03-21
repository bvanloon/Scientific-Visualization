#include "settings/visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   scale(1),
   vectorField(Settings::sim::Vector::fluidVelocity)
{
   vectorGetter = Vertex::getVectorGetter(Settings::defaults::visualization::glyphs::vector);
   this->drawMode = Settings::defaults::visualization::glyphs::defaultDrawMode;
}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

QPair<float, float> Settings::visualization::Glyphs::getCurrentMagnitudeRange() const
{
   switch (vectorField)
   {
   case Settings::sim::Vector::fluidVelocity:
      return Settings::simulation().getRange(Settings::sim::Scalar::fluidVelocityMagnitude);

   case Settings::sim::Vector::force:
      return Settings::simulation().getRange(Settings::sim::Scalar::forceFieldMagnitude);
   }
}

void Settings::visualization::Glyphs::onVectorFieldChanged(Settings::sim::Vector vectorField)
{
   this->vectorField = vectorField;
   vectorGetter = Vertex::getVectorGetter(vectorField);
}

void Settings::visualization::Glyphs::onGlyphChanged(Settings::sim::GlyphsType glyph)
{
   this->glyph = glyph;
   this->drawMode = Settings::sim::drawModes.at(glyph);
}

void Settings::visualization::Glyphs::onCellSizeChanged(QSizeF newSize)
{
   this->cellSize = newSize;
}

void Settings::visualization::Glyphs::onScaleChanged(double scale)
{
   this->scale = scale;
}
