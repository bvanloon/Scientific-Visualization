#include "abstractglyph.h"


AbstractGlyph::AbstractGlyph(float texture)
{
   this->texture = texture;
}

float AbstractGlyph::getTexture() const
{
   return texture;
}

void AbstractGlyph::setTexture(float value)
{
   texture = value;
}

QVector<QVector3D> AbstractGlyph::getGlyphPoints() const
{
   return glyphPoints;
}

void AbstractGlyph::setGlyphPoints(const QVector<QVector3D>& value)
{
   glyphPoints = value;
}
