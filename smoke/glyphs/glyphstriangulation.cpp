#include "glyphstriangulation.h"

GlyphsTriangulation::GlyphsTriangulation()
{}

void GlyphsTriangulation::extend(AbstractGlyph glyph)
{
   QVector<QVector3D> glyphPoints = glyph.getGlyphPoints();

   for (int i = 0; i < glyphPoints.length(); ++i)
   {
      this->vertices.append(glyphPoints.at(i));
      this->textureCoordinates.append(glyph.getTexture());
   }
}

QVector<QVector3D> GlyphsTriangulation::getVertices() const
{
   return vertices;
}

QVector<float> GlyphsTriangulation::getTextureCoordinates() const
{
   return textureCoordinates;
}
