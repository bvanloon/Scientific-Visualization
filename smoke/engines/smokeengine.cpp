#include "smokeengine.h"
#include "grid/triangulation.h"
#include "settings/visualizationsettings.h"

SmokeEngine::SmokeEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight)
{}

void SmokeEngine::draw(Simulation *simulation)
{
   int bufferLength = this->updateBuffers(simulation);

   drawWithMode(GL_TRIANGLES, bufferLength);
}

int SmokeEngine::updateBuffers(Simulation *simulation)
{
   Triangulation triangulation = simulation->getGridTriangulation();

   QVector<QVector3D> triangles = triangulation.getVertexPositions();

   QVector<float> textureCoordinates = simulation->getTexCoord(
               Settings::visualization::smoke().colorMap->textureGetter,
               triangulation);

   updateBuffer(this->vertexBuffer, triangles);

   //Fill normal buffer with triangles to make sure it is not empty.
   updateBuffer(this->normalBuffer, triangles);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);
   return triangles.length();
}
