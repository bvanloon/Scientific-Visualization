#include "grid/uniformgrid.h"
#include "settings/visualizationsettings.h"

UniformGrid::StreamLineBuilder::StreamLineBuilder(UniformGrid *grid, QVector3D seedPoint,
                                                  Vertex::vectorGetter vectorGetter, Vertex::scalarGetter textureGetter) :
   grid(grid),
   vectorGetter(vectorGetter),
   textureGetter(textureGetter)
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
      next = interpolate(current);
      succes = tryAddingEdge(current, next);

      current = next;
      time += this->timeStep;
   }
}

bool UniformGrid::StreamLineBuilder::terminate(double currentTime)
{
   return currentTime > this->maximumTime;
}

bool UniformGrid::StreamLineBuilder::isEdgeAllowed(QVector3D origin, QVector3D destination)
{
   // - Streamline goes out of the computational domain: isVertexAllowed();
   // - streamLineLength > maximumLength

   return true;
}

bool UniformGrid::StreamLineBuilder::isVertexAllowed(QVector3D vertex)
{
   //Is vertex within the computational domain?
   return true;
}

bool UniformGrid::StreamLineBuilder::tryAddingEdge(QVector3D previousPosition, QVector3D position)
{
   if (!this->isEdgeAllowed(previousPosition, position)) return false;

   //Find texture coordinate for destination
//   Cell *cell = this->grid->findCellContaining(position);
   float textureCoordinate = 0.0;

   this->streamLine.addVertex(position, textureCoordinate);

   return true;
}

bool UniformGrid::StreamLineBuilder::tryAddingSeedPoint(QVector3D seedPoint)
{
   if (!this->isVertexAllowed(seedPoint)) return false;

   //Find texture coordinate for seedpoint
   Cell *cell = this->grid->findCellContaining(seedPoint);
   float textureCoordinate = 0.0;

   this->streamLine.addVertex(seedPoint, textureCoordinate);

   return true;
}

QVector3D UniformGrid::StreamLineBuilder::interpolate(QVector3D previous)
{
   //Euler will do just fine for now
   return previous + 3 * previous + QVector3D(20.0, 20.0, 0.0);
}
