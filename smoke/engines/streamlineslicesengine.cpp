#include "streamlineslicesengine.h"

StreamLineSlicesEngine::StreamLineSlicesEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::noLight),
   grid(simulationGrid)
{}

void StreamLineSlicesEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(this->drawMode, bufferLength);
}

int StreamLineSlicesEngine::updateBuffers()
{
   GPUData data = buildStreamLines();

   AbstractEngine::updateBuffers(data);
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
