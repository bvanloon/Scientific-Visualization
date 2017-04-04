#include "translucentstreamlinebuilder.h"


TranslucentStreamLineBuilder::TranslucentStreamLineBuilder(
   UniformGrid *grid,
   QVector3D currentPosition,
   Vertex::vectorGetter vectorGetter,
   Vertex::scalarGetter magnitudeGetter,
   Range<double> magnitudeRange
   ) :
   AbstractTranslucentBuilder(magnitudeRange),
   StreamLineBuilder(grid, currentPosition, vectorGetter, magnitudeGetter)
{
   qDebug() << "TranslucentStreamLineBuilder::TranslucentStreamLineBuilder";
}
