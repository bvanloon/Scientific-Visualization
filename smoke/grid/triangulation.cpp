#include "triangulation.h"
#include "grid/cell.h"

Triangulation::Triangulation()
{}

Triangulation::Triangulation(int numVertices)
{
    vertexPositions.reserve(numVertices);
    vertices.reserve(numVertices);
}

void Triangulation::extend(Triangulation *other)
{
    vertexPositions.append(other->vertexPositions);
    vertices.append(other->vertices);
}

void Triangulation::extend(Triangulation other)
{
    vertexPositions.append(other.vertexPositions);
    vertices.append(other.vertices);
}

QVector<QVector3D> Triangulation::getVertexPositions() const
{
    return vertexPositions;
}

QVector<Vertex *> Triangulation::getVertices() const
{
    return vertices;
}

void Triangulation::addVertex(Vertex *value)
{
    vertices.append(value);
    vertexPositions.append(*(value->getPosition()));
}

int Triangulation::numVertices()
{
    return this->vertices.size();
}
