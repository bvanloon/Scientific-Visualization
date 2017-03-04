#include "glyphdata.h"

GlyphData::GlyphData()
{}

GlyphData::GlyphData(int numGlyphs)
{
    positions.reserve(numGlyphs);
    vectors.reserve(numGlyphs);
    scalars.reserve(numGlyphs);
}

void GlyphData::extend(GlyphData *other)
{
    extend(*other);
}

void GlyphData::extend(GlyphData other)
{
    positions.append(other.positions);
    vectors.append(other.vectors);
    scalars.append(other.scalars);
}

void GlyphData::addGlyph(QVector3D position, QVector2D vector, float scalar)
{
    positions.append(position);
    vectors.append(vector.normalized());
    scalars.append(scalar);
}

