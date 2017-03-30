#include "simulationstatehistory.h"
#include "settings/visualizationsettings.h"

SimulationStateHistory::SimulationStateHistory(QObject *parent) :
   QObject(parent),
   numberOfStatesToStore(Settings::visualization::slices().numberOfSlices)
{}

void SimulationStateHistory::addState(StateGrid *stateGrid)
{
   this->states.enqueue(stateGrid);
   if (this->historyTooLong()) trimHistoryToMaximumSize();
}

bool SimulationStateHistory::historyTooLong()
{
   return this->states.size() > this->numberOfStatesToStore;
}

void SimulationStateHistory::trimHistoryToMaximumSize()
{
   while (this->historyTooLong())
   {
      deleteOldestState();
   }
}

void SimulationStateHistory::deleteOldestState()
{
   StateGrid *oldestState = this->states.dequeue();

   delete oldestState;
}

const SimulationStateHistory& SimulationStateHistory::instance()
{
   static SimulationStateHistory instance;

   return instance;
}

void SimulationStateHistory::onNumberOfSlicesChanged(int numberOfSlices)
{
   this->numberOfStatesToStore = numberOfSlices;
}

void SimulationStateHistory::onNewSimulationState(UniformGrid *currentSimulationState)
{
   StateGrid *state = new StateGrid(currentSimulationState);

   this->addState(state);
}
