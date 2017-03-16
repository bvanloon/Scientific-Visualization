#include "cone.h"
#include <math.h>

Cone::Cone() :
   center(QVector3D(0, 0, 0)),
   direction(QVector3D(0, 1, 0)),
   height(1.0f)
{}

mesh::TriangleMesh *Cone::toTriangleMesh(int resolution)
{
   Cone::MeshBuilder builder = MeshBuilder(this, resolution);
   return builder.getMesh();
}

mesh::TriangleMesh *Cone::MeshBuilder::getMesh() const
{
   return mesh;
}

int Cone::MeshBuilder::computeNumFaces()
{
   return 2 * this->resolution;
}

int Cone::MeshBuilder::computeNumVertices()
{
   return this->resolution + 2;
}

Cone::MeshBuilder::MeshBuilder(Cone *cone, int resolution) :
   cone(cone),
   resolution(resolution)
{
   mesh = new mesh::TriangleMesh(computeNumVertices(), computeNumFaces());
}

QVector3D Cone::MeshBuilder::computeTop()
{
   return this->cone->center + 0.5 * this->cone->height * this->cone->direction;
}

QVector3D Cone::MeshBuilder::computeBottomCenter()
{
   return this->cone->center - 0.5 * this->cone->height * this->cone->direction;
}
