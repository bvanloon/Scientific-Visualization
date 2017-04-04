#include "abstractglyph.h"
#include <assert.h>
#include "settings/visualizationsettings.h"
#include "utilities/range.h"


AbstractGlyph::AbstractGlyph()
{}

GPUData AbstractGlyph::toGPUData(float textureCoordinate, float alpha)
{
   GPUData data(this->getDrawMode());
   data.addElements(vertices, normals, textureCoordinate, alpha);
   return data;
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
   Range<double> range = Settings::visualization::glyphs().getCurrentMagnitudeRange();
   return mapToUnitRange(direction.length(), (float) range.minimum(), (float) range.maximum());
}

float AbstractGlyph::computeBaseSize(float cellRatio)
{
   QSizeF cellSize = Settings::visualization::glyphs().approxCellSize;
   return cellRatio * qMax(cellSize.width(), cellSize.height());
}
