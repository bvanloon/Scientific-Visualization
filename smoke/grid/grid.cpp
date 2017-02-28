#include "grid.h"

Grid::Grid(int numberOfVertices):
    vertices(numberOfVertices),
    vertexPositions(numberOfVertices)
{}

const QVector<QVector3D> &Grid::getVertexPositions() const
{
    return this->vertexPositions;
}

const QVector<Vertex> &Grid::getVertices() const
{
    return this->vertices;
}

const int &Grid::numVertices() const
{
    return this->vertexPositions.size();
}
