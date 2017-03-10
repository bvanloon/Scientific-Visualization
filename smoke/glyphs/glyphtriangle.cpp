#include "glyphtriangle.h"

GlyphTriangle::GlyphTriangle()
{}

GlyphTriangle::GlyphTriangle(QVector3D a, QVector3D b, QVector3D c)
{
   this->pointA = a;
   this->pointB = b;
   this->pointC = c;
}

QVector3D GlyphTriangle::getA()
{
   return this->pointA;
}

QVector3D GlyphTriangle::getB()
{
   return this->pointB;
}

QVector3D GlyphTriangle::getC()
{
   return this->pointC;
}

QVector<QVector3D> GlyphTriangle::getVertices()
{
   QVector<QVector3D> vertices;
   vertices.append(pointA);
   vertices.append(pointB);
   vertices.append(pointC);

   return vertices;
}

void GlyphTriangle::setPointA(const QVector3D& value)
{
   pointA = value;
}

void GlyphTriangle::setPointB(const QVector3D& value)
{
   pointB = value;
}

void GlyphTriangle::setPointC(const QVector3D& value)
{
   pointC = value;
}
