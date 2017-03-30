#include "simulationstatehistory.h"
#include "settings/visualizationsettings.h"

SimulationStateHistory::SimulationStateHistory(QObject *parent) :
   QObject(parent),
   numberOfStatesToStore(Settings::visualization::slices().numberOfSlices)
{}

void SimulationStateHistory::addState(StateGrid *StateGrid)
{
   qDebug() << "Adding a state!";
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
