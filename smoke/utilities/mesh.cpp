#include "mesh.h"
#include <QDebug>

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

void mesh::Vertex::addAdjacentFace(mesh::Triangle *face)
{
   this->adjacentFaces.append(face);
}

QVector3D mesh::Vertex::forwardPointingNormal()
{
   QVector3D normal;

   for (auto face : adjacentFaces)
   {
      normal += face->forwardPointingNormal();
   }
   return normal.normalized();
}

QVector3D mesh::Triangle::forwardPointingNormal()
{
   QVector3D ab = vertexA->position() - vertexB->position();
   QVector3D ac = vertexA->position() - vertexC->position();

   return QVector3D::crossProduct(ab, ac).normalized();
}

QList<mesh::Vertex *> mesh::Triangle::getVertices()
{
   QList<Vertex *> vertices;
   vertices.append(vertexA);
   vertices.append(vertexB);
   vertices.append(vertexC);
   return vertices;
}

QVector<QVector3D> mesh::Triangle::getVertexPositions()
{
   QVector<QVector3D> positions;
   positions.append(vertexA->position());
   positions.append(vertexB->position());
   positions.append(vertexC->position());
   return positions;
}

QVector<QVector3D> mesh::Triangle::getVertexNormals()
{
   QVector<QVector3D> normals;
   normals.append(vertexA->forwardPointingNormal());
   normals.append(vertexB->forwardPointingNormal());
   normals.append(vertexC->forwardPointingNormal());
   return normals;
}

bool mesh::Triangle::hasCCWwindingOrder()
{
   QVector3D ab = vertexB->position() - vertexA->position();
   QVector3D ac = vertexC->position() - vertexA->position();
   double crossProductZ = ab.x() * ac.y() - ab.y() * ac.x();

   return crossProductZ > 0.0;
}

void mesh::Triangle::swapVertices()
{
   Vertex *temp = vertexA;

   vertexA = vertexB;
   vertexB = temp;
}

mesh::TriangleMesh::TriangleMesh(int numVertices, int numFaces)
{
   //Avoid resizing while adding elements, which invalidates the pointer references.
   vertices.reserve(numVertices);
   vertexPositions.reserve(numVertices);
   triangles.reserve(numFaces);
}

mesh::TriangleMesh::~TriangleMesh()
{
   for (auto vertex : vertices)
   {
      delete vertex;
   }
   for (auto triangle : triangles)
   {
      delete triangle;
   }
}

mesh::Vertex *mesh::TriangleMesh::addVertex(QVector3D position)
{
   this->vertexPositions.append(position);
   QVector3D *positionPtr = &vertexPositions.last();
   Vertex *newVertex = new Vertex(positionPtr);
   this->addVertex(newVertex);
   return newVertex;
}

mesh::Triangle *mesh::TriangleMesh::addTriangle(mesh::Vertex *a, mesh::Vertex *b, mesh::Vertex *c)
{
   Triangle *triangle = new Triangle(a, b, c);

   a->addAdjacentFace(triangle);
   b->addAdjacentFace(triangle);
   c->addAdjacentFace(triangle);
   this->triangles.append(triangle);
   return triangle;
}

QVector<QVector3D> mesh::TriangleMesh::getVerticesAsVBO() const
{
   QVector<QVector3D> vertices;
   for (auto triangle : this->triangles)
   {
      vertices.append(triangle->getVertexPositions());
   }
   return vertices;
}

QVector<QVector3D> mesh::TriangleMesh::getNormalsAsVBO() const
{
   QVector<QVector3D> normals;
   for (auto triangle : this->triangles)
   {
      normals.append(triangle->getVertexNormals());
   }
   return normals;
}

QVector<QVector3D> mesh::TriangleMesh::getVertexPositions() const
{
   return vertexPositions;
}

void mesh::TriangleMesh::applyTransformation(QMatrix4x4 transformationMatrix)
{
   QVector4D transformedPosition;

   for (int i = 0; i < numVertices(); i++)
   {
      transformedPosition = transformationMatrix * QVector4D(vertexPositions[i], 1.0);
      vertexPositions.replace(i, transformedPosition.toVector3D());
   }
}

int mesh::TriangleMesh::numVertices()
{
    return this->vertexPositions.length();
}

int mesh::TriangleMesh::numVBOVertices()
{
    return this->triangles.length() * 3;
}

mesh::Vertex *mesh::TriangleMesh::addVertex(mesh::Vertex *vertex)
{
   this->vertices.append(vertex);
   return vertex;
}
