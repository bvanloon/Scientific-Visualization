#include "triangulation.h"

Triangulation::Triangulation(int numVertices):
    vertexPositions(numVertices),
    vertices(numVertices)
{

}


Triangulation *Triangulation::fromCell(Cell *cell)
{

}

QVector<QVector3D> Triangulation::getVertexPositions() const
{
    return vertexPositions;
}

QVector<Vertex *> Triangulation::getVertices() const
{
    return vertices;
}
