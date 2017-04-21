#include "translucentstreamlinebuilder.h"
#include "settings/visualization/streamlines.h"

TranslucentStreamLineBuilder::TranslucentStreamLineBuilder(
   const UniformGrid *grid,
   QVector3D currentPosition,
   Range<double> magnitudeRange
   ) :
   AbstractTranslucentBuilder(magnitudeRange),
   StreamLineBuilder(grid, currentPosition, &Settings::visualization::streamLines())
{}

bool TranslucentStreamLineBuilder::tryAddingVertex(QVector3D position)
{
   float magnitude = this->computeMagnitude(position);
   bool magnitudeAllowed = this->isMagnitudeLargeEnough(magnitude);
   float alpha = computeAlpha(magnitude);

   if (magnitudeAllowed) this->streamLine.addVertex(position, magnitude, alpha);
   return magnitudeAllowed;
}
