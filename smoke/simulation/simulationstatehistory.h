#ifndef SIMULATIONSTATEHISTORY_H
#define SIMULATIONSTATEHISTORY_H

#include <QObject>
#include <QQueue>

#include "grid/uniformgrid.h"
#include "simulation/simulationdata.h"

class SimulationStateHistory : public QObject
{
   Q_OBJECT

   public:
      static const SimulationStateHistory& instance();

      ~SimulationStateHistory();

   signals:

   public slots:
      void onNumberOfSlicesChanged(int numberOfSlices);

      void onNewSimulationState(SimulationData *simulationDataDeepCopy);

      void onWindowResized(QSizeF newSize);

   private slots:

   private:
      explicit SimulationStateHistory(QObject *parent = 0);
      SimulationStateHistory(SimulationStateHistory const&) = delete;
      void operator=(SimulationStateHistory const&) = delete;


      int numberOfStatesToStore;
      QQueue<SimulationData *> states;
      SimulationGrid *mirrorSimulationGrid;

      void addState(SimulationData *state);

      bool historyTooLong();

      void trimHistoryToMaximumSize();

      void deleteOldestState();
};

#endif // SIMULATIONSTATEHISTORY_H
