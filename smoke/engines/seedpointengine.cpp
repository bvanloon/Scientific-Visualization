#include "seedpointengine.h"

SeedPointEngine::SeedPointEngine() :
    AbstractEngine(AbstractEngine::lightModel::noLight)
{
    qDebug() << "SeedPointEngine::SeedPointEngine";
}

int SeedPointEngine::updateBuffers()
{
    qDebug() << "SeedPointEngine::updateBuffers()";
}

void SeedPointEngine::draw(Simulation *UNUSED(Simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(drawMode, bufferLength);
}
