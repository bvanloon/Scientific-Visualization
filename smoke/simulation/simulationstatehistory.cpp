#include "simulationstatehistory.h"
#include "settings/visualizationsettings.h"

SimulationStateHistory::SimulationStateHistory(QObject *parent) :
   QObject(parent),
   QQueue(QQueue<StateGrid>()),
   numberOfStatesToStore(Settings::visualization::slices().numberOfSlices)
{}

const SimulationStateHistory& SimulationStateHistory::instance()
{
   static SimulationStateHistory instance;

   return instance;
}

void SimulationStateHistory::onNumberOfSlicesChanged(int numberOfSlices)
{
   this->numberOfStatesToStore = numberOfSlices;
}
