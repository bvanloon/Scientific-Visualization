#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QPoint>
#include <float.h>
#include "grid/simulationgrid.h"
#include "grid/glyphdata.h"

#include "simulation/simulationrealization.h"
#include "grid/triangulation.h"

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

   public slots:

      void onMouseMoved(QPoint newPosition);

      void onStep();

      void onWindowResized(int width, int height);

   private:
      SimulationRealization *realization;
      SimulationGrid *grid;

      QPoint lastMousePosition;
};

#endif // SMOKE_H
