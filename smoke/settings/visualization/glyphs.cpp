#include "settings/visualization/glyphs.h"
#include "settings/simulationsettings.h"
#include "settings/visualizationsettings.h"
#include <QDebug>

Settings::visualization::Glyphs::Glyphs(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   vectorField(Settings::sim::Vector::fluidVelocity),
   glyph(Settings::sim::GlyphsType::airplane),
   scale(1.0),
   jitterFactor(0.4),
   gridDimension(20, 20)
{
   vectorGetter = Vertex::getVectorGetter(vectorField);
}

const Settings::visualization::Glyphs& Settings::visualization::Glyphs::instance()
{
   static Glyphs instance;

   return instance;
}

Range<double> Settings::visualization::Glyphs::getCurrentMagnitudeRange() const
{
   switch (vectorField)
   {
   case Settings::sim::Vector::fluidVelocity:
      return Settings::simulation().getRange(Settings::sim::Scalar::fluidVelocityMagnitude);

   case Settings::sim::Vector::force:
      return Settings::simulation().getRange(Settings::sim::Scalar::forceFieldMagnitude);

   case Settings::sim::Vector::fluidDensityGradient:
      return this->computeGradientMagnitudeRange(
                   Settings::simulation().getRange(Settings::sim::Scalar::fluidDensity).maximum());

   case Settings::sim::Vector::fluidVelocityMagnitudeGradient:
      return this->computeGradientMagnitudeRange(
                    Settings::simulation().getRange(Settings::sim::Scalar::fluidVelocityMagnitude).maximum());

   default:
      qDebug() << "Settings::visualization::Glyphs::getCurrentMagnitudeRange(): Current VectorField is not supported. Using default fluidVelocityMagnitude ";
      return Settings::simulation().getRange(Settings::sim::Scalar::fluidVelocityMagnitude);
   }
}

Range<double> Settings::visualization::Glyphs::computeGradientMagnitudeRange(double maximumGradientValue) const
{
   double maxX = maximumGradientValue / Settings::visualization::glyphs().approxCellSize.width();
   double maxY = maximumGradientValue / Settings::visualization::glyphs().approxCellSize.height();

   double maximum = QVector2D(maxX, maxY).length();

   return Range<double>(0.0, maximum);
}

void Settings::visualization::Glyphs::onVectorFieldChanged(Settings::sim::Vector vectorField)
{
   this->vectorField = vectorField;
   vectorGetter = Vertex::getVectorGetter(vectorField);
   emit clearCache();
}

void Settings::visualization::Glyphs::onGlyphChanged(Settings::sim::GlyphsType glyph)
{
   this->glyph = glyph;
   emit clearCache();
}

void Settings::visualization::Glyphs::onCellSizeChanged(QSizeF newSize)
{
   this->approxCellSize = newSize;
   emit clearCache();
}

void Settings::visualization::Glyphs::onScaleChanged(double scale)
{
   this->scale = scale;
   emit clearCache();
}

void Settings::visualization::Glyphs::onGridDimensionChanged(QSizeF newDimension)
{
   gridDimension = newDimension.toSize();
   emit gridDimensionChanged(newDimension);
   emit replaceGrid();
   emit clearCache();
}

void Settings::visualization::Glyphs::onJitterFactorChanged(double newJitterFactor)
{
   jitterFactor = newJitterFactor;
   emit replaceGrid();
   emit clearCache();
}
