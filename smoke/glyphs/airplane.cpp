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
   position(position),
   orthogonalDirection(computeOrthogonalVector(direction)),
   mesh(4, 2)
{
   mesh::Vertex *tail = mesh.addVertex(position);
   mesh::Vertex *nose = mesh.addVertex(computeNose());
   mesh::Vertex *rightWing = mesh.addVertex(computeRightWing());
   mesh::Vertex *leftWing = mesh.addVertex(computeLeftWing());

   mesh.addTriangle(leftWing, nose, tail);
   mesh.addTriangle(tail, nose, rightWing);
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

float Airplane::AirplaneBuilder::baseEdgeLength()
{
   return maxSize + minSize;
}

QVector3D Airplane::AirplaneBuilder::computeNose()
{
   float height = this->baseEdgeLength() * SIN60;

   return this->position + height * this->direction;
}

QVector3D Airplane::AirplaneBuilder::computeLeftWing()
{
   return this->computeWing(-1);
}

QVector3D Airplane::AirplaneBuilder::computeRightWing()
{
   return this->computeWing(+1);
}

QVector3D Airplane::AirplaneBuilder::computeWing(int direction)
{
   return position + 0.5 * baseEdgeLength() * orthogonalDirection * direction;
}
