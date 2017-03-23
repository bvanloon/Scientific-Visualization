#include "streamlineengine.h"
#include "utilities/gpudata.h"

StreamLineEngine::StreamLineEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::noLight),
   grid(simulationGrid)
{}

int StreamLineEngine::updateBuffers()
{
    GPUData data;
    data.addElement(QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0), 0.0);
    data.addElement(QVector3D(200.0, 200.0, 0.0), QVector3D(0.0, 0.0, 1.0), 0.01);

    this->AbstractEngine::updateBuffers(data);
    return data.numElements();
}

void StreamLineEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(this->drawMode, bufferLength);
}
