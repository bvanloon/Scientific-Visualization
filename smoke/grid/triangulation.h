#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
#include <grid/vertex.h>

class Triangulation
{
   public:

      Triangulation();
      Triangulation(int numVertices);

      void extend(Triangulation *other);

      void extend(Triangulation other);

      void addVertex(Vertex *value);

      void transform(QMatrix4x4 transformationMatrix);

      int numVertices();

      QVector<QVector3D> getVertexPositions() const;

      QVector<Vertex *> getVertices() const;

   private:
      QVector<QVector3D> vertexPositions;
      QVector<Vertex *> vertices;
};

#endif // TRIANGULATION_H
