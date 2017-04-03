#include "translucentsmokebuilder.h"

TranslucentSmokeBuilder::TranslucentSmokeBuilder(SimulationGrid *grid, Vertex::scalarGetter textureGetter) :
   AbstractTranslucentBuilder(),
   SmokeBuilder(grid, textureGetter)
{}

void TranslucentSmokeBuilder::addVertex(Vertex *vertex)
{
   static bool printed = false;
   if (!printed)
   {
      qDebug() << "TranslucentSmokeBuilder::addVertex";
      printed = true;
   }
   double textureCoordinate = (vertex->*getTextureCoordinate)();
   QVector3D position = *vertex->getPosition();
   data.addElement(position, normal, textureCoordinate);
}
