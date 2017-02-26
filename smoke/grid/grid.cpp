#include "grid.h"

Grid::Grid(int numberOfVertices):
    vertices(numberOfVertices),
    vertexPositions(numberOfVertices)
{}

const QVector<QVector3D> &Grid::getVertexPositions() const
{
    return this->vertexPositions;
}
