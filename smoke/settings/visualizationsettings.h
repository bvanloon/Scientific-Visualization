#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settings.h"
#include "simulation/simulation.h"

class Settings::visualization::ColorMap : public QObject {
   Q_OBJECT
   public:
      explicit ColorMap(QObject *parent = 0);

      Settings::visualization::ScalarVariable scalar;
};

class Settings::visualization::Smoke : public QObject {
   Q_OBJECT
   public:
      static const Smoke& instance();

   private:
      explicit Smoke(QObject *parent = 0);

      Settings::visualization::ColorMap colorMap;

      Smoke(Smoke const&) = delete;
      void operator=(Smoke const&) = delete;
};

class Settings::visualization::Glyphs : public QObject {
   Q_OBJECT
   public:
      static const Glyphs& instance();

   private:
      explicit Glyphs(QObject *parent = 0);

      Settings::visualization::ColorMap colorMap;

      Glyphs(Glyphs const&) = delete;
      void operator=(Glyphs const&) = delete;
};

class Settings::VisualizationClassOld : public QObject
{
   Q_OBJECT
   public:

      static const VisualizationClassOld& instance();

      ::Simulation::textureCoordinateGetter textureGetter;
      visualization::ScalarVariable scalar;

      float vectorScale;

   signals:
      void valueRangeChanged(float minimum, float maximum);

   public slots:
      void onTextureVariableChanged(Settings::visualization::ScalarVariable scalarVariable);

   private:
      explicit VisualizationClassOld(QObject *parent = 0);

      VisualizationClassOld(VisualizationClassOld const&) = delete;
      void operator=(VisualizationClassOld const&) = delete;

      void setScalarVariableToFluidDensity();

      void setScalarVariableToFluidVelocityMagnitude();

      void setScalarVariableToForceFieldMagnitude();
};

#endif // VISUALIZATIONS_H
