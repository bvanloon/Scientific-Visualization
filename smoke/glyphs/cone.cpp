#include "cone.h"
#include "settings/visualizationsettings.h"
#include "shapes/cone.h"

const double Cone::maxCellRatio = 1.0;

Cone::Cone(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar),
   mesh(::shapes::Cone().toTriangleMesh())
{
   rotate(direction);
   scale(computeNormalizedMagnitude(direction));
   translate(position);
}

void Cone::translate(QVector3D position)
{}

void Cone::scale(float scalingFactor)
{}

void Cone::rotate(QVector3D direction)
{}

float Cone::computeScalingFactor(QVector3D direction)
{
   return computeBaseSize(maxCellRatio) *
          computeNormalizedMagnitude(direction) *
          Settings::visualization::glyphs().scale;
}
