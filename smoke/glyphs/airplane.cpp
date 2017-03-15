#include "airplane.h"
#include "utilities/mesh.h"

Airplane::Airplane(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
    AirplaneBuilder boeing = AirplaneBuilder(position, direction);
    addVertices(boeing.getVertices(), boeing.getNormals());
}

Airplane::AirplaneBuilder::AirplaneBuilder(QVector3D position, QVector3D direction) :
   position(position),
   direction(direction)
{}

QVector<QVector3D> Airplane::AirplaneBuilder::getNormals()
{
   QVector<QVector3D> normals;
   normals.fill(QVector3D(0.0, 0.0, 1.0), 3);
   return normals;
}

QVector<QVector3D> Airplane::AirplaneBuilder::getVertices()
{
    QVector<QVector3D> vertices;
    vertices.append(QVector3D(10.00, 20.0, 0.0));
    vertices.append(QVector3D(200.0, 100.0, 0.0));
    vertices.append(QVector3D(100.0, 150.0, 0.0));
    return vertices;
}
