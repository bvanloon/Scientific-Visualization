#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector>

namespace mesh {
    class Vertex;
    class Triangle;

    class TriangleMesh
    {
       public:
          TriangleMesh();

          Vertex *addVertex(QVector3D position);

       private:
          QVector<QVector3D> vertexPositions;
          QVector<Vertex *> vertices;

          Vertex *addVertex(Vertex *vertex);
    };

    class Vertex
    {
       public:
          Vertex(QVector3D *position);

          QVector3D position() const;

    private:
          QVector3D *positionPtr;
    };

    class Triangle
    {
       public:
          Triangle(Vertex *vertexA, Vertex *vertexB, Vertex *vertexc);

          QVector3D computeForwardPointingFaceNormal();

       private:
          Vertex *vertexA;
          Vertex *vertexB;
          Vertex *vertexC;

          bool hasCCWwindingOrder();

          void swapVertices();
    };
}

#endif // MESH_H
