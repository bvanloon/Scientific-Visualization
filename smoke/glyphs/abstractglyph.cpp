#include "abstractglyph.h"


AbstractGlyph::AbstractGlyph(float texture)
{
   this->textureCoordinate = texture;
}

float AbstractGlyph::getTextureCoordinate() const
{
   return textureCoordinate;
}

QVector<QVector3D> AbstractGlyph::getVertices() const
{
   return vertices;
}
