#include "mesh.h"

mesh::Vertex::Vertex(QVector3D *position) :
   positionPtr(position)
{}

mesh::Triangle::Triangle(Vertex *vertexA, Vertex *vertexB, Vertex *vertexC) :
   vertexA(vertexA), vertexB(vertexB), vertexC(vertexC)
{
    if (!hasCCWwindingOrder()) swapVertices();
}
QVector3D mesh::Vertex::position() const
{
   return *positionPtr;
}

mesh::Triangle::Triangle(Vertex *vertexA, Vertex *vertexB, Vertex *vertexC) :
   vertexA(vertexA), vertexB(vertexB), vertexC(vertexC)
{
   if (!hasCCWwindingOrder()) swapVertices();
}

QVector3D mesh::Triangle::computeForwardPointingFaceNormal()
{
   QVector3D ab = vertexB->position() - vertexA->position();
   QVector3D ac = vertexC->position() - vertexA->position();

   return QVector3D::crossProduct(ac, ab).normalized();
}

bool mesh::Triangle::hasCCWwindingOrder()
{
   QVector3D ab = vertexB->position() - vertexA->position();
   QVector3D ac = vertexC->position() - vertexA->position();
   double crossProductZ = ab.x() * ac.y() - ab.y() * ac.x();

   return crossProductZ < 0.0;
}

void mesh::Triangle::swapVertices()
{
   Vertex *temp = vertexA;

   vertexA = vertexB;
   vertexB = temp;
}

mesh::TriangleMesh::TriangleMesh()
{}

mesh::Vertex *mesh::TriangleMesh::addVertex(QVector3D position)
{
   this->vertexPositions.append(position);
   Vertex *newVertex = new Vertex(&vertexPositions.last());
   this->addVertex(newVertex);
   return newVertex;
}

mesh::Triangle *mesh::TriangleMesh::addTriangle(mesh::Vertex *a, mesh::Vertex *b, mesh::Vertex *c)
{
   Triangle *triangle = new Triangle(a, b, c);

   this->triangles.append(triangle);
}
mesh::Vertex *mesh::TriangleMesh::addVertex(mesh::Vertex *vertex)
{
   this->vertices.append(vertex);
   return vertex;
}
