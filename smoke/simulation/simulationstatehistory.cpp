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
                              Settings::visualization::glyphs().gridDimension.width(),
                              Settings::canvas().size,
                              Settings::visualization::glyphs().jitterFactor,
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

const SimulationGrid& SimulationHistory::getCombinedSimulationGridOfLastStates(int numStates, SimulationGridUpdater updateSimulationGrid) const
{
   (this->*updateSimulationGrid)(numStates);
   return *mirrorSimulationGrid;
}

const UniformGrid& SimulationHistory::getVisualizationGridAtQueueIdx(int idx) const
{
   SimulationData *state = this->getStateAtQueueIdx(idx);
   mirrorSimulationGrid->setData(state);
   return *this->mirrorVisualizationGrid;
}

const UniformGrid& SimulationHistory::getCombinedVisualizationGridOfLastStates(int numStates, SimulationGridUpdater updateSimulationGrid) const
{
   (this->*updateSimulationGrid)(numStates);
   return *mirrorVisualizationGrid;
}

int SimulationHistory::mostRecentStateIdx() const
{
   int idx = this->states.size() - 1;
   return idx;
}

int SimulationHistory::size() const
{
   return this->states.size();
}

void SimulationHistory::onHistorySizeChanged(int size)
{
   if (size > states.getMaximumSize()) this->states.changeMaximumSize(size);
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

void SimulationHistory::updateSimulationGridToLastState(int UNUSED(numStates)) const
{
   static SimulationData *dataPtr = nullptr;
   if (dataPtr != nullptr) delete dataPtr;
   QList<SimulationData *> statesToUse = this->states.tail(1);
   //Hacky hack
   dataPtr = new SimulationData(SimulationData::mean(statesToUse));
   mirrorSimulationGrid->setData(dataPtr);
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

void SimulationHistory::onReplaceGrid()
{
   delete mirrorVisualizationGrid;
   mirrorVisualizationGrid = JitterGrid::createVisualizationGrid(
                 Settings::visualization::glyphs().gridDimension.width(),
                 Settings::canvas().size,
                 Settings::visualization::glyphs().jitterFactor,
                mirrorSimulationGrid);
}
