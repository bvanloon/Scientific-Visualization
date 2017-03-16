#include "cone.h"

Cone::Cone() :
   center(QVector3D(0, 0, 0)),
   direction(QVector3D(0, 1, 0)),
   height(1.0f)
{}

mesh::TriangleMesh *Cone::toTriangleMesh(int resolution)
{
    mesh::TriangleMesh mesh = mesh::TriangleMesh(
                computeNumVertices(resolution),
                computeNumFaces(resolution));
    mesh::Vertex* top = mesh.addVertex(computeTop());
    mesh::Vertex* bottomCenter = mesh.addVertex(computeBottomCenter());
}

int Cone::computeNumFaces(int resolution)
{
   return 2 * resolution;
}

int Cone::computeNumVertices(int resolution)
{
   return resolution + 2;
}

QVector3D Cone::computeTop()
{
   return this->center + 0.5 * this->height * this->direction;
}

QVector3D Cone::computeBottomCenter()
{
   return this->center - 0.5 * this->height * this->direction;
}
