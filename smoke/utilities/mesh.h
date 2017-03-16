#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector>
#include <QList>
#include <QMatrix4x4>

namespace mesh {
    class Vertex;
    class Triangle;

    class TriangleMesh
    {
       public:
          TriangleMesh(int numVertices, int numFaces);

          ~TriangleMesh();

          Vertex *addVertex(QVector3D position);

          Triangle *addTriangle(Vertex *a, Vertex *b, Vertex *c);

          QVector<QVector3D> getVerticesAsVBO() const;
          QVector<QVector3D> getNormalsAsVBO() const;
          QVector<QVector3D> getVertexPositions() const;

          void applyTransformation(QMatrix4x4 transformationMatrix);

          int numVertices();

    private:
          QVector<QVector3D> vertexPositions;
          QVector<Vertex *> vertices;
          QVector<Triangle *> triangles;

          Vertex *addVertex(Vertex *vertex);
    };

    class Vertex
    {
       public:
          Vertex(QVector3D *position);

          QVector3D position() const;

          void addAdjacentFace(Triangle *face);

          QVector3D forwardPointingNormal();

       private:
          QVector3D *positionPtr;
          QList<Triangle *> adjacentFaces;
    };

    class Triangle
    {
       public:
          Triangle(Vertex *vertexA, Vertex *vertexB, Vertex *vertexc);

          QVector3D forwardPointingNormal();

          QList<Vertex *> getVertices();

          QVector<QVector3D> getVertexPositions();

          QVector<QVector3D> getVertexNormals();

       private:
          Vertex *vertexA;
          Vertex *vertexB;
          Vertex *vertexC;

          bool hasCCWwindingOrder();

          void swapVertices();
    };
}

#endif // MESH_H
