#include "airplane.h"

Airplane::Airplane(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   addVertex(QVector3D(10.00, 20.0, 0.0), QVector3D(0.0, 0.0, 1.0));
   addVertex(QVector3D(200.0, 100.0, 0.0), QVector3D(0.0, 0.0, 1.0));
   addVertex(QVector3D(100.0, 150.0, 0.0), QVector3D(0.0, 0.0, 1.0));
}
