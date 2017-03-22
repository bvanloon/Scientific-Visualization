#include "seedpointengine.h"

SeedPointEngine::SeedPointEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight)
{}

int SeedPointEngine::updateBuffers()
{
   QVector<QVector3D> vertices;
   vertices.append(QVector3D(100, 200, 0));
   vertices.append(QVector3D(400, 450, 0));
   vertices.append(QVector3D(100, 200, 0));
   updateBuffer(this->vertexBuffer, vertices);
   updateBuffer(this->textureCoordinateBuffer, QVector<float>(vertices.size(), 0.5));
   updateBuffer(this->normalBuffer, QVector<QVector3D>(vertices.size(), QVector3D(0.0, 0.0, 1.0)));
   return vertices.size();
}

void SeedPointEngine::draw(Simulation *UNUSED(Simulation))
{
   qDebug() << "SeedPointEngine::draw";
   int bufferLength = this->updateBuffers();

   drawWithMode(drawMode, bufferLength);
}
