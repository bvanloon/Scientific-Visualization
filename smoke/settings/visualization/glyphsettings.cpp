#include "settings/visualizationsettings.h"
#include <QDebug>
#include "settings/simulationsettings.h"

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   vectorScale(1),
   magnitude(Settings::sim::fluidVelocityMagnitude)
{
   vectorGetter = Vertex::getVectorGetter(Settings::defaults::visualization::glyphs::vector);
   this->drawMode = Settings::defaults::visualization::glyphs::defaultDrawMode;
}

void Settings::visualization::Glyphs::setMagnitude(Settings::sim::Vector vectorField)
{
   switch (vectorField)
   {
   case Settings::sim::Vector::fluidVelocity:
      this->magnitude = Settings::sim::Scalar::fluidVelocityMagnitude;
      break;

   case Settings::sim::Vector::force:
      this->magnitude = Settings::sim::Scalar::forceFieldMagnitude;
      break;
   }
}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

QPair<float, float> Settings::visualization::Glyphs::getCurrentMagnitudeRange() const
{
   return Settings::simulation().getRange(this->magnitude);
}

void Settings::visualization::Glyphs::onVectorFieldChanged(Settings::sim::Vector vectorField)
{
   vectorGetter = Vertex::getVectorGetter(vectorField);
   this->setMagnitude(vectorField);
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
