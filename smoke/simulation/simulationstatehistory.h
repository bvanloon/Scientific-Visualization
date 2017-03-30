#ifndef SIMULATIONSTATEHISTORY_H
#define SIMULATIONSTATEHISTORY_H

#include <QObject>
#include <QQueue>

#include "grid/stategrid.h"

class SimulationStateHistory : public QObject
{
   Q_OBJECT

   public:
      static const SimulationStateHistory& instance();

   signals:

   public slots:
      void onNumberOfSlicesChanged(int numberOfSlices);

   private slots:

   private:
      explicit SimulationStateHistory(QObject *parent = 0);
      SimulationStateHistory(SimulationStateHistory const&) = delete;
      void operator=(SimulationStateHistory const&) = delete;

      int numberOfStatesToStore;

      QQueue<StateGrid> states;
};

#endif // SIMULATIONSTATEHISTORY_H
