#ifndef SIMULATIONSTATEHISTORY_H
#define SIMULATIONSTATEHISTORY_H

#include <QObject>
#include <QQueue>

#include "grid/stategrid.h"
#include "grid/uniformgrid.h"

class SimulationStateHistory : public QObject
{
   Q_OBJECT

   public:
      static const SimulationStateHistory& instance();

   signals:

   public slots:
      void onNumberOfSlicesChanged(int numberOfSlices);
      void onNewSimulationState(UniformGrid* currentSimulationState);

   private slots:

   private:
      explicit SimulationStateHistory(QObject *parent = 0);
      SimulationStateHistory(SimulationStateHistory const&) = delete;
      void operator=(SimulationStateHistory const&) = delete;


      int numberOfStatesToStore;
      QQueue<StateGrid> states;

      void addState(StateGrid* StateGrid);
};

#endif // SIMULATIONSTATEHISTORY_H
