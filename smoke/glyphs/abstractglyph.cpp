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

QVector<QVector3D> AbstractGlyph::getNormals() const
{
    return normals;
}

void AbstractGlyph::addVertex(QVector3D vertex, QVector3D normal)
{
    this->vertices.append(vertex);
    this->normals.append(normal);
}
