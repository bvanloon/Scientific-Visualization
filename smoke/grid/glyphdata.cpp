#include "glyphdata.h"

GlyphData::GlyphData()
{}

GlyphData::GlyphData(int numGlyphs)
{
   positions.reserve(numGlyphs);
   directions.reserve(numGlyphs);
   textureCoordinates.reserve(numGlyphs);
}

int GlyphData::numGlyphs()
{
   return positions.size();
}

void GlyphData::extend(GlyphData *other)
{
   extend(*other);
}

void GlyphData::extend(GlyphData other)
{
   positions.append(other.positions);
   directions.append(other.directions);
   textureCoordinates.append(other.textureCoordinates);
}

void GlyphData::addGlyph(QVector3D position, QVector2D direction, float textureCoordinate)
{
   this->positions.append(position);
   this->directions.append(direction);
   this->textureCoordinates.append(textureCoordinate);
}

QVector<QVector3D> GlyphData::getPositions() const
{
   return positions;
}

QVector<QVector3D> GlyphData::getDirections() const
{
   return directions;
}

QVector<float> GlyphData::getTextureCoordinates() const
{
   return textureCoordinates;
}
