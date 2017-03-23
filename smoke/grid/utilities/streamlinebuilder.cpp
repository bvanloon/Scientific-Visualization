#include "grid/uniformgrid.h"
#include "settings/visualizationsettings.h"

UniformGrid::StreamLineBuilder::StreamLineBuilder(Grid *grid, QVector3D seedPoint, Vertex::vectorGetter vectorGetter, Vertex::scalarGetter textureGetter):
    grid(grid),
    seedPoint(seedPoint),
    vectorGetter(vectorGetter),
    textureGetter(textureGetter)
{
    this->timeStep = Settings::visualization::streamLines().timeStep;
    this->maximumTime = Settings::visualization::streamLines().maximumTime;

    this->edgeLength = Settings::visualization::streamLines().edgeLength;
    this->maximumTotalLength = Settings::visualization::streamLines().totalLength;
}

streamobject::Line UniformGrid::StreamLineBuilder::getStreamLine()
{
    this->streamLine.addVertex(this->seedPoint, 0.0);
    this->streamLine.addVertex(this->seedPoint + 2 * this->seedPoint, 0.0);

    return streamLine;
}
