#include "translucentsmokebuilder.h"

TranslucentSmokeBuilder::TranslucentSmokeBuilder(SimulationGrid *grid,
                                                 Vertex::scalarGetter textureGetter,
                                                 Range textureRange) :
   AbstractTranslucentBuilder(textureRange),
   SmokeBuilder(grid, textureGetter)
{}

void TranslucentSmokeBuilder::addVertex(Vertex *vertex)
{
   double textureCoordinate = (vertex->*getTextureCoordinate)();
   QVector3D position = *vertex->getPosition();
   data.addElement(position, normal, textureCoordinate);
}
