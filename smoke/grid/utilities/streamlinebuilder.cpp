#include "grid/utilities/streamlinebuilder.h"
#include "settings/visualizationsettings.h"

const float UniformGrid::StreamLineBuilder::minimumMagnitude = std::numeric_limits<float>::min();

UniformGrid::StreamLineBuilder::StreamLineBuilder(UniformGrid *grid, QVector3D seedPoint,
                                                  Vertex::vectorGetter vectorGetter, Vertex::scalarGetter magnitudeGetter) :
   grid(grid),
   vectorGetter(vectorGetter),
   magnitudeGetter(magnitudeGetter),
   currentMagnitudeIsLargeEnough(true)
{
   this->timeStep = Settings::visualization::streamLines().timeStep;
   this->maximumTime = Settings::visualization::streamLines().maximumTime;

   this->edgeLength = Settings::visualization::streamLines().edgeLength;
   this->maximumTotalLength = Settings::visualization::streamLines().totalLength;

   build(seedPoint);
}

streamobject::Line UniformGrid::StreamLineBuilder::getStreamLine()
{
   return this->streamLine;
}

void UniformGrid::StreamLineBuilder::build(QVector3D seedPoint)
{
   double time = 0.0;
   QVector3D next, current = seedPoint;

   bool succes = tryAddingSeedPoint(current);

   while (!terminate(time) && succes)
   {
      next = integrate(current);
      succes = tryAddingEdge(current, next);

      current = next;
      time += this->timeStep;
   }
}

bool UniformGrid::StreamLineBuilder::terminate(double currentTime)
{
   return (!hasTimeLeftOver(currentTime)) ||
          (!this->currentMagnitudeIsLargeEnough);
}

bool UniformGrid::StreamLineBuilder::isEdgeAllowed(QVector3D origin, QVector3D destination)
{
   return this->isVertexAllowed(destination) &&
          this->isNewStreamLineLengthAllowed(origin, destination);
}

bool UniformGrid::StreamLineBuilder::isVertexAllowed(QVector3D vertex)
{
   return this->grid->inGridArea(vertex);
}

bool UniformGrid::StreamLineBuilder::isMagnitudeNearZero(float magnitude)
{
   return magnitude <= UniformGrid::StreamLineBuilder::minimumMagnitude;
}

bool UniformGrid::StreamLineBuilder::hasTimeLeftOver(double currentTime)
{
   return currentTime <= this->maximumTime;
}

bool UniformGrid::StreamLineBuilder::isNewStreamLineLengthAllowed(QVector3D origin, QVector3D destination)
{
   double edgeLength = (destination - origin).length();
   double potentialStreamLineLength = this->streamLine.getLength() + edgeLength;

   return potentialStreamLineLength < this->maximumTotalLength;
}

bool UniformGrid::StreamLineBuilder::tryAddingVertex(QVector3D position)
{
   float magnitude = this->computeMagnitude(position);

   this->streamLine.addVertex(position, magnitude);
   return true;
}

bool UniformGrid::StreamLineBuilder::tryAddingEdge(QVector3D previousPosition, QVector3D position)
{
   if (!this->isEdgeAllowed(previousPosition, position)) return false;

   bool succes = this->tryAddingVertex(position);
   return succes;
}

bool UniformGrid::StreamLineBuilder::tryAddingSeedPoint(QVector3D seedPoint)
{
   if (!this->isVertexAllowed(seedPoint)) return false;

   bool succes = this->tryAddingVertex(seedPoint);
   return succes;
}

float UniformGrid::StreamLineBuilder::computeMagnitude(QVector3D position)
{
   StructuredCell *cell = this->grid->findCellContaining(position);
   float textureCoordinate = cell->interpolateScalar(position, this->magnitudeGetter);

   return textureCoordinate;
}

QVector3D UniformGrid::StreamLineBuilder::integrate(QVector3D previousPosition)
{
   //Euler will do just fine for now
   QVector3D previousVector = this->grid->findCellContaining(previousPosition)->interpolate2DVector(previousPosition, this->vectorGetter);
   QVector3D currentPosition = previousPosition + previousVector.normalized() * this->edgeLength;

   return currentPosition;
}
