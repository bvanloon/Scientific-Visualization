#include "abstractglyph.h"


AbstractGlyph::AbstractGlyph(float texture)
{
   this->textureCoordinate = texture;
}

float AbstractGlyph::getTextureCoordinate() const
{
   return textureCoordinate;
}

void AbstractGlyph::setTextureCoordinate(float value)
{
   textureCoordinate = value;
}

QVector<QVector3D> AbstractGlyph::getVertices() const
{
   return vertices;
}

void AbstractGlyph::setVertices(const QVector<QVector3D>& value)
{
   vertices = value;
}
