#include "translucentsmokebuilder.h"

TranslucentSmokeBuilder::TranslucentSmokeBuilder(const SimulationGrid *grid,
                                                 Vertex::scalarGetter textureGetter,
                                                 Range<double> textureRange) :
   AbstractTranslucentBuilder(textureRange),
   SmokeBuilder(grid, textureGetter)
{}

void TranslucentSmokeBuilder::addVertex(Vertex *vertex)
{
   double textureCoordinate = (vertex->*getTextureCoordinate)();
   QVector3D position = *vertex->getPosition();
   double alpha = computeAlpha(textureCoordinate);
   data.addElement(position, normal, textureCoordinate, alpha);
}
