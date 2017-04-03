#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include <QSizeF>

#include "settings.h"
#include "simulation/simulation.h"
#include "settings/visualization/streamlines.h"
#include "settings/visualization/glyphs.h"
#include "settings/visualization/slices.h"

#include "grid/vertex.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Settings::visualization::ColorMap : public QObject {
   Q_OBJECT
   public:
      explicit ColorMap(QObject *parent = 0);

      Settings::sim::Scalar scalar;
      Vertex::scalarGetter textureGetter;

   signals:
      void valueRangeChanged(Settings::sim::Scalar scalarVariable, float minimum, float maximum);
      void clearCache();

   public slots:
      void onTextureVariableChanged(Settings::sim::Scalar scalarVariable);
};

class Settings::visualization::Smoke : public QObject {
   Q_OBJECT
   public:
      static const Smoke& instance();

      Settings::visualization::ColorMap *colorMap;
   signals:
      void clearCache();

   private:
      explicit Smoke(QObject *parent = 0);
      Smoke(Smoke const&) = delete;
      void operator=(Smoke const&) = delete;
};

#endif // VISUALIZATIONS_H
