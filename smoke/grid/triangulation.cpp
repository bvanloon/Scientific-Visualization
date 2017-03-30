#include "triangulation.h"
#include "grid/cell.h"

Triangulation::Triangulation()
{}

Triangulation::Triangulation(int numVertices)
{
   vertexPositions.reserve(numVertices);
   vertices.reserve(numVertices);
}

Triangulation::~Triangulation()
{
    vertexPositions.clear();
    vertices.clear();
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

void Triangulation::transform(QMatrix4x4 transformationMatrix)
{
    QVector4D transformedPosition;
    for (int i = 0; i < this->numVertices(); i++)
    {
       transformedPosition = transformationMatrix * QVector4D(this->vertexPositions[i], 1.0);
       this->vertexPositions.replace(i, transformedPosition.toVector3D());
    }
}
int Triangulation::numVertices()
{
   return this->vertices.size();
}
