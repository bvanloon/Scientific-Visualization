#include "streamlineslicesengine.h"

StreamLineSlicesEngine::StreamLineSlicesEngine(UniformGrid *simulationGrid) :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::streamLineSlices),
   grid(simulationGrid)
{}

void StreamLineSlicesEngine::draw(Simulation *UNUSED(simulation))
{
    GPUData newData = buildStreamLines();
    this->cache.enqueue(newData);

    drawSlices(this->drawMode);
}

int StreamLineSlicesEngine::fillBuffers(Simulation *UNUSED(Simulation))
{
   GPUData data = buildStreamLines();

   updateBuffers(data);
   return data.numElements();
}

GPUData StreamLineSlicesEngine::buildStreamLines()
{
   GPUData data;

   for (QPointF seedpoint : Settings::visualization::streamLines().seedPoints)
   {
      GPUData streamLine = buildStreamLine(seedpoint);
      data.extend(streamLine);
   }
   return data;
}

GPUData StreamLineSlicesEngine::buildStreamLine(QPointF seedPoint)
{
   streamobject::Line streamLine = grid->computeStreamLine(QVector3D(seedPoint),
                                                            Settings::visualization::streamLines().colorMap->textureGetter,
                                                            Settings::visualization::streamLines().vectorField);
   return streamLine.toGPUData();
}
