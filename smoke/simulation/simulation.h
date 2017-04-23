#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>
#include <QPoint>
#include "grid/simulationgrid.h"
#include "simulation/simulationrealization.h"

class Simulation : public QObject {
   Q_OBJECT

   public:

      explicit Simulation(QObject *parent = 0);
      ~Simulation();

      SimulationGrid *getSimulationGrid() const;

      void step();

   signals:
      void newSimulationState(SimulationData *deepCopyOfNewSimulationData);
      void newSimulationState();

      void updateDynamicRange(Settings::sim::Scalar scalar, Range<double> range);

   public slots:

      void onMouseMoved(QPoint newPosition);

      void onStep();

      void onWindowResized(int width, int height);

   private:
      SimulationRealization *realization;
      SimulationGrid *grid;

      QPoint lastMousePosition;

      void connectToSettings();

      void emitUpdatesOfDynamicRanges();
};

#endif // SMOKE_H
