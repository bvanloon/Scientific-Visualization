#include "streamlineengine.h"
#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"
#include "visualizationbuilders/streamlinebuilder.h"

StreamLineEngine::StreamLineEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::streamLines),
   grid(simulationGrid)
{}

GPUData StreamLineEngine::buildStreamLines()
{
   GPUData data(streamobject::Line::drawMode);

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      GPUData streamLine = buildStreamLine(seedpoint);
      data.extend(streamLine);
   }
   return data;
}

GPUData StreamLineEngine::buildStreamLine(QPointF seedPoint)
{
   StreamLineBuilder builder(grid, QVector3D(seedPoint),
                             Settings::visualization::streamLines().vectorField,
                             Settings::visualization::streamLines().colorMap->textureGetter);
   streamobject::Line streamLine = builder.getStreamLine();

   return streamLine.GPUDataEdges();
}

void StreamLineEngine::draw()
{
   GPUData data = buildStreamLines();
   updateBuffersAndDraw(data);
}
