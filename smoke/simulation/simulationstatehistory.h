#ifndef SIMULATIONSTATEHISTORY_H
#define SIMULATIONSTATEHISTORY_H

#include <QObject>
#include <QQueue>

#include "grid/simulationgrid.h"
#include "simulation/simulationdata.h"
#include "grid/jittergrid.h"

class SimulationStateHistory : public QObject
{
   Q_OBJECT

   public:
      static const SimulationStateHistory& instance();

      ~SimulationStateHistory();

      const SimulationGrid& getSimulationGridAtQueueIdx(int idx) const;

   signals:

   public slots:
      void onNumberOfSlicesChanged(int numberOfSlices);

      void onNewSimulationState(SimulationData *simulationDataDeepCopy);

      void onWindowResized(QSizeF newWindowSize);

      void onGridDimensionChanged(QSizeF newDimension);

   private slots:

   private:
      explicit SimulationStateHistory(QObject *parent = 0);
      SimulationStateHistory(SimulationStateHistory const&) = delete;
      void operator=(SimulationStateHistory const&) = delete;


      int numberOfStatesToStore;
      QQueue<SimulationData *> states;
      SimulationGrid *mirrorSimulationGrid;
      UniformGrid *mirrorVisualizationGrid;

      void addState(SimulationData *state);

      SimulationData *getStateAtQueueIdx(int idx) const;

      int timeToQueueIdx(int time);

      bool historyTooLong();

      void trimHistoryToMaximumSize();

      void deleteOldestState();
};

#endif // SIMULATIONSTATEHISTORY_H
