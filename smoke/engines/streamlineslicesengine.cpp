#include "streamlineslicesengine.h"

StreamLineSlicesEngine::StreamLineSlicesEngine(UniformGrid *simulationGrid) :
   AbstractSliceEngine(AbstractEngine::lightModel::noLight,
                       Settings::engines::EnginesTypes::streamLineSlices),
   grid(simulationGrid)
{}

void StreamLineSlicesEngine::draw(Simulation *simulation)
{
   int bufferLength = this->fillBuffers(simulation);

   drawWithMode(this->drawMode, bufferLength);
}

int StreamLineSlicesEngine::fillBuffers(Simulation *UNUSED(Simulation))
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
