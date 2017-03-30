#include "simulationstatehistory.h"
#include "settings/visualizationsettings.h"

SimulationStateHistory::SimulationStateHistory(QObject *parent) :
   QObject(parent),
   numberOfStatesToStore(Settings::visualization::slices().numberOfSlices)
{}

void SimulationStateHistory::addState(SimulationData *state)
{
   this->states.enqueue(state);
   if (this->historyTooLong()) trimHistoryToMaximumSize();
}

bool SimulationStateHistory::historyTooLong()
{
   return this->states.size() > this->numberOfStatesToStore;
}

void SimulationStateHistory::trimHistoryToMaximumSize()
{
   while (this->historyTooLong()) { deleteOldestState(); }
}

void SimulationStateHistory::deleteOldestState()
{
   SimulationData *oldestState = this->states.dequeue();

   delete oldestState;
}

const SimulationStateHistory& SimulationStateHistory::instance()
{
   static SimulationStateHistory instance;

   return instance;
}

SimulationStateHistory::~SimulationStateHistory()
{
   for (auto state : states) delete state;
}

void SimulationStateHistory::onNumberOfSlicesChanged(int numberOfSlices)
{
   this->numberOfStatesToStore = numberOfSlices;
}

void SimulationStateHistory::onNewSimulationState(SimulationData *simulationDataDeepCopy)
{
   addState(simulationDataDeepCopy);
}
