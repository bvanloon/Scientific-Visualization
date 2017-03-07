#include "smokeengine.h"
#include "grid/triangulation.h"

SmokeEngine::SmokeEngine() :
   AbstractEngine()
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

   QVector<float> textureCoordinates = (simulation->*Settings::visualization().textureGetter)(triangulation);

   updateBuffer(this->vertexBuffer, triangles);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);
   return triangles.length();
}
