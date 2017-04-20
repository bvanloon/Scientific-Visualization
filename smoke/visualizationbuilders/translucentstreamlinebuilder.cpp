#include "translucentstreamlinebuilder.h"
#include "settings/visualization/streamlines.h"

TranslucentStreamLineBuilder::TranslucentStreamLineBuilder(
   const UniformGrid *grid,
   QVector3D currentPosition,
   Vertex::scalarGetter magnitudeGetter,
   Range<double> magnitudeRange
   ) :
   AbstractTranslucentBuilder(magnitudeRange),
   StreamLineBuilder(grid, currentPosition, magnitudeGetter, &Settings::visualization::streamLines())
{}

bool TranslucentStreamLineBuilder::tryAddingVertex(QVector3D position)
{
   float magnitude = this->computeMagnitude(position);
   bool magnitudeAllowed = this->isMagnitudeLargeEnoguh(magnitude);
   float alpha = computeAlpha(magnitude);

   if (magnitudeAllowed) this->streamLine.addVertex(position, magnitude, alpha);
   return magnitudeAllowed;
}
