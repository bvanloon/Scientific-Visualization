#ifndef GLYPHS_H
#define GLYPHS_H

#include <QObject>
#include "grid/vertex.h"
#include "settings/settings.h"
#include "utilities/range.h"

class Settings::visualization::Glyphs : public QObject
{
   Q_OBJECT

   public:
      static const Glyphs& instance();

      Settings::visualization::ColorMap *colorMap;

      Vertex::vectorGetter vectorGetter;
      Settings::sim::Vector vectorField;

      Settings::sim::GlyphsType glyph;

      QSizeF approxCellSize;
      float scale;

      double jitterFactor;

      Range<double> getCurrentMagnitudeRange() const;

   signals:
      void gridDimensionChanged(QSizeF newDimension);

      void clearCache();

   public slots:
      void onVectorFieldChanged(Settings::sim::Vector vectorField);

      void onGlyphChanged(Settings::sim::GlyphsType glyph);

      void onCellSizeChanged(QSizeF newSize);

      void onScaleChanged(double scale);

      void onGridDimensionChanged(QSizeF newDimension);

      void onJitterFactorChanged(double newJitterFactor);

   private:
      explicit Glyphs(QObject *parent = 0);
      Glyphs(Glyphs const&) = delete;
      void operator=(Glyphs const&) = delete;

      Range<double> computeGradientMagnitudeRange(double maximumGradientValue) const;
};

#endif // GLYPHS_H
