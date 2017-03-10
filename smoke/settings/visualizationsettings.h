#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settings.h"
#include "simulation/simulation.h"
#include "grid/vertex.h"

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

private:
      Vertex::scalarGetter getTextureGetter(Settings::sim::Scalar scalarVariable);
};

class Settings::visualization::Smoke : public QObject {
   Q_OBJECT
   public:
      static const Smoke& instance();

      Settings::visualization::ColorMap *getColorMap() const;

private:
      explicit Smoke(QObject *parent = 0);
      Smoke(Smoke const&) = delete;
      void operator=(Smoke const&) = delete;

      Settings::visualization::ColorMap* colorMap;
};

class Settings::visualization::Glyphs : public QObject {
   Q_OBJECT
   public:
      static const Glyphs& instance();

      Settings::visualization::ColorMap *getColorMap() const;

      float vectorScale;

private:
      explicit Glyphs(QObject *parent = 0);
      Glyphs(Glyphs const&) = delete;
      void operator=(Glyphs const&) = delete;

      Settings::visualization::ColorMap* colorMap;
};

class Settings::VisualizationClassOld : public QObject
{
   Q_OBJECT
   public:

      static const VisualizationClassOld& instance();

      ::Simulation::textureCoordinateGetter textureGetter;
      ::Settings::sim::Scalar scalar;

   signals:
      void valueRangeChangedOld(float minimum, float maximum);

   public slots:
      void onTextureVariableChangedOld(Settings::sim::Scalar scalarVariable);

   private:
      explicit VisualizationClassOld(QObject *parent = 0);

      VisualizationClassOld(VisualizationClassOld const&) = delete;
      void operator=(VisualizationClassOld const&) = delete;

      void setScalarVariableToFluidDensity();

      void setScalarVariableToFluidVelocityMagnitude();

      void setScalarVariableToForceFieldMagnitude();
};

#endif // VISUALIZATIONS_H
