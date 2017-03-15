#include "airplane.h"
#include "utilities/vector.h"
#include <QDebug>

#define SIN60    0.86602540378

const float Airplane::AirplaneBuilder::minSize = 1;
const float Airplane::AirplaneBuilder::maxSize = 20;

Airplane::Airplane(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   AirplaneBuilder builder = AirplaneBuilder(position, direction);

   addVertices(builder.getVertices(), builder.getNormals());
}

Airplane::AirplaneBuilder::AirplaneBuilder(QVector3D position, QVector3D direction) :
   direction(direction.normalized()),
   mesh(4, 2)
{
   float edgeLength = maxSize + minSize;
   float height = edgeLength * SIN60;

   QVector3D orthogonalDirection = computeOrthogonalVector(this->direction);

   mesh::Vertex *d = mesh.addVertex(position);
   mesh::Vertex *b = mesh.addVertex(d->position() + height * this->direction);
   mesh::Vertex *c = mesh.addVertex(d->position() + 0.5 * edgeLength * orthogonalDirection);
   mesh::Vertex *a = mesh.addVertex(d->position() - 0.5 * edgeLength * orthogonalDirection);

   mesh.addTriangle(a, b, d);
   mesh.addTriangle(d, b, c);
}

QVector<QVector3D> Airplane::AirplaneBuilder::getNormals()
{
   QVector<QVector3D> normals;
   for (auto triangle : mesh.getTriangles())
   {
      normals.append(triangle->getVertexNormals());
   }
   return normals;
}

QVector<QVector3D> Airplane::AirplaneBuilder::getVertices()
{
   QVector<QVector3D> vertices;
   for (auto triangle : mesh.getTriangles())
   {
      vertices.append(triangle->getVertexPositions());
   }
   return vertices;
}
