#include "streamlineslicesengine.h"
#include "settings/visualizationsettings.h"
#include "visualizationbuilders/translucentstreamlinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreamLineSlicesEngine::StreamLineSlicesEngine() :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::streamLineSlices)
{
   connectToSettings();
}

void StreamLineSlicesEngine::updateCache()
{
   this->cache.enqueue(buildStreamLines());
}

GPUData StreamLineSlicesEngine::buildStreamLines()
{
   GPUData data;

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      GPUData streamLine = buildStreamLine(
                  &SimulationHistory::instance().getCombinedSimulationGridOfLastStates(
                      Settings::visualization::slices().numStatesPerSlice,
                      Settings::visualization::slices().combinationMethod),
                  seedpoint);
      data.extend(streamLine);
   }
   return data;
}

GPUData StreamLineSlicesEngine::buildStreamLine(const SimulationGrid *grid, QPointF seedPoint)
{
   TranslucentStreamLineBuilder builder(grid, QVector3D(seedPoint),
                                        Settings::simulation().getMagnitudeRange(Settings::visualization::streamLines().vectorField));
   streamobject::Line streamLine = builder.buildLine();
   return streamLine.GPUDataEdges();
}

void StreamLineSlicesEngine::connectToSettings()
{
   connect(&Settings::visualization::streamLines(), SIGNAL(clearCache()),
            this, SLOT(onClearCache()));
}
