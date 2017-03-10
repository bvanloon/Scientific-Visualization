#ifndef GLYPHTRIANGLE_H
#define GLYPHTRIANGLE_H

#include <QVector>
#include <QVector3D>

class GlyphTriangle
{
   public:
      GlyphTriangle();
      GlyphTriangle(QVector3D a, QVector3D b, QVector3D c);
      QVector3D getA();

      QVector3D getB();

      QVector3D getC();

      QVector<QVector3D> getVertices();

      void setPointA(const QVector3D& value);

      void setPointB(const QVector3D& value);

      void setPointC(const QVector3D& value);

   private:
      QVector3D pointA, pointB, pointC;
};

#endif // GLYPHTRIANGLE_H
