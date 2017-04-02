#include "smokeengine.h"
#include "grid/triangulation.h"
#include "settings/visualizationsettings.h"

SmokeEngine::SmokeEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::smoke)
{}

void SmokeEngine::draw(Simulation *simulation)
{
   int bufferLength = this->fillBuffers(simulation);

   drawWithMode(GL_TRIANGLES, bufferLength);
}

int SmokeEngine::fillBuffers(Simulation *simulation)
{
   Triangulation triangulation = simulation->getGridTriangulation();

   Vertex::scalarGetter textureGetter = Settings::visualization::smoke().colorMap->textureGetter;
   GPUData data = GPUData(GL_TRIANGLES);
   QVector3D normal = QVector3D(0.0, 0.0, 1.0);
   double textureCoordinate;

   for(Vertex* vertex : triangulation.getVertices()){
        textureCoordinate = (vertex->*textureGetter)();
        data.addElement(*vertex->getPosition(), normal, textureCoordinate);
   }

   updateBuffers(data);
   return triangulation.numVertices();
}
