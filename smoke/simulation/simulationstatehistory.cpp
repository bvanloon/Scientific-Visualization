#include "simulationstatehistory.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

SimulationHistory::SimulationHistory(QObject *parent) :
   QObject(parent),
   states(Settings::visualization::slices().numSlices),
   mirrorSimulationGrid(new SimulationGrid(
                           Settings::simulation().dimension,
                           Settings::canvas().size,
                           NULL)),
   mirrorVisualizationGrid(JitterGrid::createVisualizationGrid(
                              Settings::defaults::visualization::glyphs::gridSize.width(),
                              Settings::canvas().size,
                              mirrorSimulationGrid))
{}

SimulationHistory::~SimulationHistory()
{}

const SimulationHistory& SimulationHistory::instance()
{
   static SimulationHistory instance;

   return instance;
}

void SimulationHistory::addState(SimulationData *state)
{
   this->states.enqueue(state);
}

const SimulationGrid& SimulationHistory::getSimulationGridAtQueueIdx(int idx) const
{
   SimulationData *state = this->getStateAtQueueIdx(idx);
   mirrorSimulationGrid->setData(state);
   return *this->mirrorSimulationGrid;
}

const SimulationGrid& SimulationHistory::getMeanSimulationGridOfLastStates(int numStates) const
{
   updateSimulationGridToMeanOfLastStates(numStates);
   return *mirrorSimulationGrid;
}

const UniformGrid& SimulationHistory::getVisualizationGridAtQueueIdx(int idx) const
{
   SimulationData *state = this->getStateAtQueueIdx(idx);
   mirrorSimulationGrid->setData(state);
   return *this->mirrorVisualizationGrid;
}

const UniformGrid& SimulationHistory::getMeanVisualizationGridOfLastStates(int numStates) const
{
   updateSimulationGridToMeanOfLastStates(numStates);
   return *mirrorVisualizationGrid;
}

int SimulationHistory::mostRecentStateIdx() const
{
   int idx = this->states.size() - 1;
   return idx;
}

void SimulationHistory::onHistorySizeChanged(int size)
{
   this->states.changeMaximumSize(size);
}

SimulationData *SimulationHistory::getStateAtQueueIdx(int idx) const
{
   return this->states.at(idx);
}

void SimulationHistory::updateSimulationGridToMeanOfLastStates(int numStates) const
{
   static SimulationData *meanPtr = nullptr;
   if (meanPtr != nullptr) delete meanPtr;
   QList<SimulationData *> statesToUse = this->states.tail(numStates);
   meanPtr = new SimulationData(SimulationData::mean(statesToUse));
   mirrorSimulationGrid->setData(meanPtr);
}

void SimulationHistory::onNewSimulationState(SimulationData *simulationDataDeepCopy)
{
   addState(simulationDataDeepCopy);
}

void SimulationHistory::onWindowResized(QSizeF newWindowSize)
{
   mirrorSimulationGrid->changeGridArea(newWindowSize);
   mirrorVisualizationGrid->changeGridArea(newWindowSize, mirrorSimulationGrid->getCellSize());
}

void SimulationHistory::onGridDimensionChanged(QSizeF newDimension)
{
   delete mirrorVisualizationGrid;
   mirrorVisualizationGrid = JitterGrid::createVisualizationGrid(
                newDimension.width(),
                Settings::canvas().size,
                mirrorSimulationGrid);
}
