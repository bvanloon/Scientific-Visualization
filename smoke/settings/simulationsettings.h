#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include <QSizeF>
#include <QMultiMap>
#include "settings.h"
#include "utilities/range.h"

class Settings::Simulation : public QObject
{
   Q_OBJECT
   public:

      static const Simulation& instance();

      int dimension;
      float timestep;
      bool frozen;
      float force;
      QSizeF cellSize;
      bool useDynamicValueRange;

      const float simulationTimeStepMinimum = 0.35;
      const float simulationTimeStepMaximum = 0.45;


      Range<double> getRange(Settings::sim::Scalar scalar) const;

      Range<double> getMagnitudeRange(Settings::sim::Vector vector) const;

   signals:
      void valueRangeChanged(Settings::sim::Scalar scalar, float minimum, float maximum);

      void toggleFrozen(bool frozen);

      void recomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void cellSizeChanged(QSizeF cellSize);

   public slots:
      void onDimensionChanged(int newDimension);

      void onForceChanged(float newForce);

      void onWindowResized(int width, int height);

      void onToggleFrozen();

      void onToggleFrozenKeyboard();

      void onTimeStepChanged(float value);

      void onUseDynamicValueRangeToggled(bool toggle);

      void onUpdateDynamicRange(Settings::sim::Scalar scalar, Range<double> range);

      void onAllConnectionsAreSetUp();

   private:
      explicit Simulation(QObject *parent = 0);

      Simulation(Simulation const&) = delete;
      void operator=(Simulation const&) = delete;

      QMultiMap<Settings::sim::Scalar, Range<double> > staticScalarRanges;
      QMultiMap<Settings::sim::Scalar, Range<double> > dynamicScalarRanges;

      void updateRange(Settings::sim::Scalar scalar, QMultiMap<sim::Scalar, Range<double> > *rangeList, float minimum, float maximum);

      void updateStaticRange(Settings::sim::Scalar scalar, float minimum, float maximum);

      void updateDynamicRange(Settings::sim::Scalar scalar, float minimum, float maximum);

      void updateGridCellSize();

      void updateGridCellSize(int canvasWidth, int height);

      void emitRange(Settings::sim::Scalar scalar);

      void switchToDynamicValueRanges();

      void switchToStaticValueRanges();

      Range<double> computeGradientMagnitudeRange(double maximumGradientValue) const;
};

#endif // SIMULATIONS_H
