#include "glyphstriangulation.h"

GlyphsTriangulation::GlyphsTriangulation()
{}

void GlyphsTriangulation::extend(AbstractGlyph glyph)
{
   this->vertices.append(glyph.getVertices());
   this->textureCoordinates.insert(textureCoordinates.end(), glyph.numVertices(), glyph.getTextureCoordinate());
   this->normals.append(glyph.getNormals());
}

QVector<QVector3D> GlyphsTriangulation::getVertices() const
{
   return vertices;
}

QVector<float> GlyphsTriangulation::getTextureCoordinates() const
{
   return textureCoordinates;
}

QVector<QVector3D> GlyphsTriangulation::getNormals() const
{
    return normals;
}

int GlyphsTriangulation::numVertices()
{
    return this->vertices.length();
}
