#include "streamlineengine.h"

StreamLineEngine::StreamLineEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::noLight),
   grid(simulationGrid)
{}

int StreamLineEngine::updateBuffers(Simulation* simulation)
{
   qDebug() << "StreamLineEngine::updateBuffers";


   Triangulation triangulation = simulation->getGridTriangulation();

   QVector<QVector3D> triangles = triangulation.getVertexPositions();

   QVector<float> textureCoordinates = simulation->getTexCoord(
                Settings::visualization::streamLines().colorMap->textureGetter,
                triangulation);

   updateBuffer(this->vertexBuffer, triangles);

   //Fill normal buffer with triangles to make sure it is not empty.
   updateBuffer(this->normalBuffer, triangles);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);
   return triangles.length();
}

void StreamLineEngine::draw(Simulation *simulation)
{
   qDebug() << "StreamLineEngine::draw";
   int bufferLength = this->updateBuffers(simulation);

   drawWithMode(GL_TRIANGLES, bufferLength);
}
