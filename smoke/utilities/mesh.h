#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector>
#include <QList>

namespace mesh {
    class Vertex;
    class Triangle;

    class TriangleMesh
    {
       public:
          TriangleMesh();

          Vertex *addVertex(QVector3D position);
          Triangle *addTriangle(Vertex *a, Vertex *b, Vertex *c);

          QVector<Triangle *> getTriangles() const;

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
          void addAdjacentFace(Triangle* face);

          QVector3D forwardPointingNormal();

    private:
          QVector3D *positionPtr;
          QList<Triangle*> adjacentFaces;
    };

    class Triangle
    {
       public:
          Triangle(Vertex *vertexA, Vertex *vertexB, Vertex *vertexc);

          QVector3D forwardPointingNormal();

          QList<Vertex*> getVertices();

       private:
          Vertex *vertexA;
          Vertex *vertexB;
          Vertex *vertexC;

          bool hasCCWwindingOrder();

          void swapVertices();
    };
}

#endif // MESH_H
