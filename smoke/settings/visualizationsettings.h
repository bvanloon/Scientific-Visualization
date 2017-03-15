#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settings.h"
#include "simulation/simulation.h"
#include "grid/vertex.h"
#include <GL/gl.h>

class Settings::visualization::ColorMap : public QObject {
   Q_OBJECT
   public:
      explicit ColorMap(QObject *parent = 0);

      Settings::sim::Scalar scalar;
      Vertex::scalarGetter textureGetter;

   signals:
      void valueRangeChanged(Settings::sim::Scalar scalarVariable, float minimum, float maximum);

   public slots:
      void onTextureVariableChanged(Settings::sim::Scalar scalarVariable);
};

class Settings::visualization::Smoke : public QObject {
   Q_OBJECT
   public:
      static const Smoke& instance();

      Settings::visualization::ColorMap *colorMap;

   private:
      explicit Smoke(QObject *parent = 0);
      Smoke(Smoke const&) = delete;
      void operator=(Smoke const&) = delete;
};

class Settings::visualization::Glyphs : public QObject {
   Q_OBJECT
   public:
      static const Glyphs& instance();

      Settings::visualization::ColorMap *colorMap;

      Vertex::vectorGetter vectorGetter;
      float vectorScale;

      Settings::sim::GlyphsType glyph;
      GLint drawMode;


   public slots:
      void onVectorFieldChanged(Settings::sim::Vector vectorField);

      void onGlyphChanged(Settings::sim::GlyphsType glyph);

   private:
      explicit Glyphs(QObject *parent = 0);
      Glyphs(Glyphs const&) = delete;
      void operator=(Glyphs const&) = delete;
};

#endif // VISUALIZATIONS_H
