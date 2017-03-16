#include "cone.h"
#include "settings/visualizationsettings.h"
#include "shapes/cone.h"
#include <QMatrix4x4>
#include <QDebug>

const double Cone::maxCellRatio = 1.0;

Cone::Cone(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar),
   mesh(::shapes::Cone().toTriangleMesh())
{
    transform(position, direction);
    this->addVertices(this->mesh->getVerticesAsVBO(), this->mesh->getNormalsAsVBO());
}

void Cone::transform(QVector3D position, QVector3D direction)
{
   rotate(direction);
   scale(direction);
   translate(position);
}

void Cone::translate(QVector3D position)
{
    QMatrix4x4 translationMatrix;
    translationMatrix.translate(position);
    mesh->applyTransformation(translationMatrix);
}

void Cone::scale(QVector3D direction)
{
//    float scalingFactor = computeScalingFactor(direction);
   float scalingFactor = 10;

   QMatrix4x4 scalingMatrix;

   scalingMatrix.scale(scalingFactor);
   mesh->applyTransformation(scalingMatrix);
}

void Cone::rotate(QVector3D direction)
{}

float Cone::computeScalingFactor(QVector3D direction)
{
   return computeBaseSize(maxCellRatio) *
          computeNormalizedMagnitude(direction) *
          Settings::visualization::glyphs().scale;
}
