#include "abstractglyph.h"
#include <assert.h>
#include "settings/visualizationsettings.h"
#include "utilities/range.h"


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

QVector<QVector3D> AbstractGlyph::getNormals() const
{
   return normals;
}

size_t AbstractGlyph::numVertices()
{
   return this->vertices.length();
}

void AbstractGlyph::addVertex(QVector3D vertex, QVector3D normal)
{
   this->vertices.append(vertex);
   this->normals.append(normal);
}

void AbstractGlyph::addVertices(QVector<QVector3D> vertices, QVector3D normal)
{
   this->vertices.append(vertices);
   this->normals.insert(this->normals.end(), vertices.length(), normal);
}

void AbstractGlyph::addVertices(QVector<QVector3D> vertices, QVector<QVector3D> normals)
{
   assert(vertices.length() == normals.length());
   this->vertices.append(vertices);
   this->normals.append(normals);
}

float AbstractGlyph::computeNormalizedMagnitude(QVector3D direction)
{
   QPair<float, float> range = Settings::visualization::glyphs().getCurrentMagnitudeRange();
   return mapToUnitRange(direction.length(), range.first, range.second);
}
