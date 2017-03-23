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
   return this->isVertexAllowed(destination) &&
          this->isEdgeLengthAllowed(origin, destination);
}

bool UniformGrid::StreamLineBuilder::isVertexAllowed(QVector3D vertex)
{
   return this->grid->inGridArea(vertex);
}

bool UniformGrid::StreamLineBuilder::isEdgeLengthAllowed(QVector3D origin, QVector3D destination)
{
   double edgeLength = (destination - origin).length();
   double potentialStreamLineLength = this->streamLine.getLength() + edgeLength;

   return potentialStreamLineLength < this->maximumTotalLength;
}

void UniformGrid::StreamLineBuilder::addVertex(QVector3D position)
{
   float textureCoordinate = this->computeTextureCoordiante(position);

   this->streamLine.addVertex(position, textureCoordinate);
}

bool UniformGrid::StreamLineBuilder::tryAddingEdge(QVector3D previousPosition, QVector3D position)
{
   if (!this->isEdgeAllowed(previousPosition, position)) return false;

   this->addVertex(position);

   return true;
}

bool UniformGrid::StreamLineBuilder::tryAddingSeedPoint(QVector3D seedPoint)
{
   if (!this->isVertexAllowed(seedPoint)) return false;

   this->addVertex(seedPoint);

   return true;
}

float UniformGrid::StreamLineBuilder::computeTextureCoordiante(QVector3D position)
{
   StructuredCell *cell = this->grid->findCellContaining(position);
   float textureCoordinate = cell->interpolateScalar(position, this->textureGetter);

   return textureCoordinate;
}

QVector3D UniformGrid::StreamLineBuilder::interpolate(QVector3D previous)
{
   //Euler will do just fine for now
   return previous + previous + QVector3D(20.0, 20.0, 0.0);
}
