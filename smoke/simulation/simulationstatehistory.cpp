#include "simulationstatehistory.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

SimulationStateHistory::SimulationStateHistory(QObject *parent) :
   QObject(parent),
   numberOfStatesToStore(Settings::visualization::slices().numberOfSlices),
   mirrorSimulationGrid(new SimulationGrid(
                           Settings::simulation().dimension,
                           Settings::canvas().size,
                           NULL))
{}

SimulationStateHistory::~SimulationStateHistory()
{
   for (auto state : states) delete state;
}

const SimulationStateHistory& SimulationStateHistory::instance()
{
   static SimulationStateHistory instance;

   return instance;
}

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

const SimulationGrid &SimulationStateHistory::getSimulationGridAtQueueIdx(int idx) const
{
   SimulationData *state = this->getStateAtQueueIdx(idx);
   mirrorSimulationGrid->setData(state);
   return *this->mirrorSimulationGrid;
}

void SimulationStateHistory::onNumberOfSlicesChanged(int numberOfSlices)
{
   this->numberOfStatesToStore = numberOfSlices;
}

SimulationData *SimulationStateHistory::getStateAtQueueIdx(int idx) const
{
   return this->states.at(idx);
}

void SimulationStateHistory::onNewSimulationState(SimulationData *simulationDataDeepCopy)
{
   addState(simulationDataDeepCopy);
}

void SimulationStateHistory::onWindowResized(QSizeF newSize)
{
   this->mirrorSimulationGrid->changeGridArea(newSize);
}
