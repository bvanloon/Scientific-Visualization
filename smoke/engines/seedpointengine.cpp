#include "seedpointengine.h"

SeedPointEngine::SeedPointEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight)
{}

int SeedPointEngine::updateBuffers(Simulation *simulation)
{
    QVector<QVector3D> vertices;
    vertices.append(QVector3D(0,0,0));
    vertices.append(QVector3D(300, 20, 0));
    vertices.append(QVector3D(20, 300, 0));

    QVector<float> textureCoordinates = QVector<float>(vertices.size(), 1.0);
    QVector<QVector3D> normals = QVector<QVector3D>(vertices.size(), QVector3D(0.0, 0.0, 1.0));


   updateBuffer(this->vertexBuffer, vertices);
   updateBuffer(this->normalBuffer, normals);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);
   return vertices.length();
}

void SeedPointEngine::draw(Simulation *simulation)
{
   int bufferLength = this->updateBuffers(simulation);

   drawWithMode(drawMode, bufferLength);
}
