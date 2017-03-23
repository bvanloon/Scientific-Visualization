#include "grid/uniformgrid.h"
#include "settings/visualizationsettings.h"

UniformGrid::StreamLineBuilder::StreamLineBuilder(Grid *grid, QVector3D seedPoint, Vertex::vectorGetter vectorGetter, Vertex::scalarGetter textureGetter) :
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

   //Current isn't necessarily allowed....
   addEdge(current);

   while (!terminate(time))
   {
      next = interpolate(current);

      if (isEdgeAllowed(current, next))
      {
         addEdge(next);
      }
      else break;

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
   // - Streamline goes out of the computational domain
   // - streamLineLength > maximumLength

    static bool returnValue = true;
    if(returnValue){
        returnValue = false;
        return true;
    }
    return returnValue;
}

void UniformGrid::StreamLineBuilder::addEdge(QVector3D position)
{
   //Find texture coordinate for destination
    float textureCoordinate = 0.0;
    this->streamLine.addVertex(position, textureCoordinate);
}

QVector3D UniformGrid::StreamLineBuilder::interpolate(QVector3D previous)
{
    //Euler will do just fine for now
    return previous + 3 * previous;
}
