#ifndef GLYPHTRIANGLE_H
#define GLYPHTRIANGLE_H

#include <QVector>
#include <QVector3D>

class QTriangle
{
   public:
      QTriangle();
      QTriangle(QVector3D a, QVector3D b, QVector3D c);
      QVector3D getA();

      QVector3D getB();

      QVector3D getC();

      QVector<QVector3D> getAllVertices();

      void setVertexA(const QVector3D& value);

      void setVertexB(const QVector3D& value);

      void setVertexC(const QVector3D& value);

      QVector3D computeFaceNormal();

   private:
      QVector3D vertexA, vertexB, vertexC;
};

#endif // GLYPHTRIANGLE_H
