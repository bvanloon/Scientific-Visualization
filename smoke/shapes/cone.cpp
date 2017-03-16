#include "cone.h"
#include <math.h>
#include "utilities/vector.h"
#include <QMatrix4x4>
#include <QVector4D>

shapes::Cone::Cone() :
   center(QVector3D(0, 0, 0)),
   direction(QVector3D(0, 1, 0)),
   height(1.0f),
   radius(1.0f)
{}

mesh::TriangleMesh *shapes::Cone::toTriangleMesh(int resolution)
{
   Cone::MeshBuilder builder = MeshBuilder(this, resolution);
   return builder.getMesh();
}

mesh::TriangleMesh *shapes::Cone::MeshBuilder::getMesh() const
{
   return mesh;
}

int shapes::Cone::MeshBuilder::computeNumFaces()
{
   return 2 * this->resolution;
}

int shapes::Cone::MeshBuilder::computeNumVertices()
{
   return this->resolution + 2;
}

shapes::Cone::MeshBuilder::MeshBuilder(shapes::Cone *cone, int resolution) :
   cone(cone),
   resolution(resolution)
{
   this->perpendicularDirection = QVector3D(0, 0, 1);
   this->mesh = new mesh::TriangleMesh(computeNumVertices(), computeNumFaces());
   this->top = this->mesh->addVertex(computeTopPosition());
   this->bottomCenter = this->mesh->addVertex(computeBottomCenterPosition());
   this->addFaces();
}

QVector3D shapes::Cone::MeshBuilder::computeTopPosition()
{
   return this->cone->center + this->cone->height * this->cone->direction;
}

QVector3D shapes::Cone::MeshBuilder::computeBottomCenterPosition()
{
   return this->cone->center;
}

void shapes::Cone::MeshBuilder::addFaces()
{
   QMatrix4x4 transformationMatrix;

   transformationMatrix.rotate(360.0 / this->resolution, this->cone->direction);

   QVector4D nextPosition = QVector4D(bottomCenter->position(), 1.0) + cone->radius * perpendicularDirection;
   QVector4D currentPosition;

   mesh::Vertex *firstVertex, *nextVertex, *currentVertex;
   firstVertex = nextVertex = mesh->addVertex(nextPosition.toVector3D());

   for (int i = 1; i < this->resolution; i++)
   {
      currentPosition = nextPosition;
      currentVertex = nextVertex;

      nextPosition = currentPosition * transformationMatrix;
      nextVertex = mesh->addVertex(nextPosition.toVector3D());

      addFacesWithEdge(currentVertex, nextVertex);
   }
   addFacesWithEdge(nextVertex, firstVertex);
}

void shapes::Cone::MeshBuilder::addFacesWithEdge(mesh::Vertex *circleVertexA, mesh::Vertex *circleVertexB)
{
   addBottomFace(circleVertexA, circleVertexB);
   addSideFace(circleVertexA, circleVertexB);
}

void shapes::Cone::MeshBuilder::addBottomFace(mesh::Vertex *circleVertexA, mesh::Vertex *circleVertexB)
{
   this->mesh->addTriangle(circleVertexA, circleVertexB, this->bottomCenter);
}

void shapes::Cone::MeshBuilder::addSideFace(mesh::Vertex *circleVertexA, mesh::Vertex *circleVertexB)
{
   this->mesh->addTriangle(circleVertexA, circleVertexB, this->top);
}
