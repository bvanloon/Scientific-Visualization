#ifndef SIMULATIONSTATEHISTORY_H
#define SIMULATIONSTATEHISTORY_H

#include <QObject>

#include "utilities/sizelimitedqueue.h"
#include "grid/simulationgrid.h"
#include "simulation/simulationdata.h"
#include "grid/jittergrid.h"

class SimulationHistory : public QObject
{
   Q_OBJECT

   public:
      static const SimulationHistory& instance();

      ~SimulationHistory();

      const SimulationGrid& getSimulationGridAtQueueIdx(int idx) const;

      const SimulationGrid& getMeanSimulationGridOfLastStates(int numStates) const;

      const UniformGrid& getVisualizationGridAtQueueIdx(int idx) const;

      const UniformGrid& getMeanVisualizationGridOfLastStates(int numStates) const;

      int mostRecentStateIdx() const;

   signals:

   public slots:
      void onHistorySizeChanged(int size);

      void onNewSimulationState(SimulationData *simulationDataDeepCopy);

      void onWindowResized(QSizeF newWindowSize);

      void onGridDimensionChanged(QSizeF newDimension);

   private slots:

   private:
      explicit SimulationHistory(QObject *parent = 0);
      SimulationHistory(SimulationHistory const&) = delete;
      void operator=(SimulationHistory const&) = delete;

      SizeLimitedQueue<SimulationData *> states;

      SimulationGrid *mirrorSimulationGrid;
      UniformGrid *mirrorVisualizationGrid;

      void addState(SimulationData *state);

      SimulationData *getStateAtQueueIdx(int idx) const;

      void updateSimulationGridToMeanOfLastStates(int numStates) const;
};

#endif // SIMULATIONSTATEHISTORY_H
