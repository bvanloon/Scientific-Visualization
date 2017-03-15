#include "airplane.h"
#include "utilities/vector.h"
#include <QDebug>

#define SIN60    0.86602540378

const float Airplane::AirplaneBuilder::minSize = 10;
const float Airplane::AirplaneBuilder::maxSize = 100;

Airplane::Airplane(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   AirplaneBuilder boeing = AirplaneBuilder(QVector3D(20.0, 150.0, 0.0), QVector3D(1.0, 0.0, 0.0));
//   AirplaneBuilder boeing = AirplaneBuilder(position, direction);

   addVertices(boeing.getVertices(), boeing.getNormals());
}

Airplane::AirplaneBuilder::AirplaneBuilder(QVector3D position, QVector3D direction) :
   direction(direction)
{
   float height = (maxSize + minSize) / SIN60;

   QVector3D orthogonalDirection = computeOrthogonalVector(direction);

   mesh::Vertex *d = mesh.addVertex(position);

   mesh::Vertex *b = mesh.addVertex(d->position() + height * direction);

   mesh::Vertex *c = mesh.addVertex(d->position() + 0.5 * height * orthogonalDirection);
   mesh::Vertex *a = mesh.addVertex(d->position() - 0.5 * height * orthogonalDirection);
}

QVector<QVector3D> Airplane::AirplaneBuilder::getNormals()
{
    QVector<QVector3D> normals;
    normals.append(QVector3D(0.0, 0.0, 1.0));
    normals.append(QVector3D(0.0, 0.0, 1.0));
    normals.append(QVector3D(0.0, 0.0, 1.0));
    return normals;
}

QVector<QVector3D> Airplane::AirplaneBuilder::getVertices()
{
    QVector<QVector3D> vertices;
    vertices.append(QVector3D(10.0, 300.0, 0.0));
    vertices.append(QVector3D(220.0, 250.0, 0.0));
    vertices.append(QVector3D(100.0, 0.0, 0.0));
    return vertices;
}
