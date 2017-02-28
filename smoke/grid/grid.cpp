#include "grid.h"

Grid::Grid(int numberOfVertices, bool padding):
    vertices(numberOfVertices),
    vertexPositions(numberOfVertices),
    padding(padding)
{}

Grid::~Grid()
{
    for(int i = 0; i < vertices.size(); i++){
        delete vertices[i];
    }
}

const QVector<QVector3D> &Grid::getVertexPositions() const
{
    return this->vertexPositions;
}

const QVector<Vertex *> &Grid::getVertices() const
{
    return this->vertices;
}

int Grid::numVertices() const
{
    return this->vertexPositions.size();
}
