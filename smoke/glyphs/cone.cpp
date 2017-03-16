#include "cone.h"

Cone::Cone(QVector3D position, QVector3D direction, float scalar):
    AbstractGlyph(scalar)
{
    this->addVertex(QVector3D(20, 20, 0), QVector3D(0.0, 0.0, 1.0));
    this->addVertex(QVector3D(200, 100, 0), QVector3D(0.0, 0.0, 1.0));
    this->addVertex(QVector3D(100, 150, 0), QVector3D(0.0, 0.0, 1.0));
}

