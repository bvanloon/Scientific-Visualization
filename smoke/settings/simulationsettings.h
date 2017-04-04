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

      const float simulationTimeStepMinimum = 0.35;
      const float simulationTimeStepMaximum = 0.45;


      Range<double> getRange(Settings::sim::Scalar scalar) const;

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

   private:
      explicit Simulation(QObject *parent = 0);

      Simulation(Simulation const&) = delete;
      void operator=(Simulation const&) = delete;

      QMultiMap<Settings::sim::Scalar, Range<double>> scalarRanges;

      void updateRange(Settings::sim::Scalar scalar, float minimum, float maximum);

      void updateGridCellSize();

      void updateGridCellSize(int canvasWidth, int height);
};

#endif // SIMULATIONS_H
