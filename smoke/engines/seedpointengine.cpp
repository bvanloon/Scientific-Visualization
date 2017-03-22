#include "seedpointengine.h"

SeedPointEngine::SeedPointEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight)
{}

void SeedPointEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->updateBuffers();

   drawWithMode(drawMode, bufferLength);
}

int SeedPointEngine::updateBuffers()
{
   fillIntermediateBuffers();

   int numElementsInBuffer = intermediateBufferSize();

   updateBuffer(this->vertexBuffer, vertices);
   updateBuffer(this->normalBuffer, normals);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);

   clearIntermediateBuffers();

   return numElementsInBuffer;
}

void SeedPointEngine::fillIntermediateBuffers()
{
   vertices.append(QVector3D(0, 0, 0));
   vertices.append(QVector3D(300, 20, 0));
   vertices.append(QVector3D(20, 300, 0));

   textureCoordinates.append(QVector<float>(vertices.size(), 1.0));

   normals.append(QVector<QVector3D>(vertices.size(), QVector3D(0.0, 0.0, 1.0)));
}

void SeedPointEngine::clearIntermediateBuffers()
{
   this->vertices.clear();
   this->normals.clear();
   this->textureCoordinates.clear();
}

int SeedPointEngine::intermediateBufferSize()
{
   return this->vertices.length();
}
