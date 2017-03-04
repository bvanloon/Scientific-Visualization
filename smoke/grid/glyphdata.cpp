#include "glyphdata.h"

GlyphData::GlyphData()
{}

GlyphData::GlyphData(int numGlyphs)
{
    positions.reserve(numGlyphs);
    vectors.reserve(numGlyphs);
    scalars.reserve(numGlyphs);
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
    vectors.append(other.vectors);
    scalars.append(other.scalars);
}

void GlyphData::addGlyph(QVector3D position, QVector2D vector, float scalar)
{
    positions.append(position);
    vectors.append(vector.normalized());
    scalars.append(scalar);
}

QVector<QVector3D> GlyphData::getPositions() const
{
    return positions;
}

QVector<QVector3D> GlyphData::getVectors() const
{
    return vectors;
}

QVector<float> GlyphData::getScalars() const
{
    return scalars;
}

