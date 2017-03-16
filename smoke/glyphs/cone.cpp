#include "cone.h"
#include "settings/visualizationsettings.h"
#include "shapes/cone.h"
#include <QMatrix4x4>
#include <QDebug>
#include <math.h>

const double Cone::maxCellRatio = 2.0;

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
   float scalingFactor = computeScalingFactor(direction);

   QMatrix4x4 scalingMatrix;

   scalingMatrix.scale(scalingFactor);
   mesh->applyTransformation(scalingMatrix);
}

void Cone::rotate(QVector3D direction)
{
   //http://stackoverflow.com/questions/20177506/rotate-geometry-to-align-to-a-direction-vector
   //http://tonyobryan.com/index.php?article=28
   QVector3D rotationAxis = QVector3D::crossProduct(shapes::Cone::getDefaultDirection(), direction.normalized());
   float rotationAngle = acos(QVector3D::dotProduct(rotationAxis.normalized(), direction.normalized()));

   QMatrix4x4 rotationMatrix;

   rotationMatrix.rotate(rotationAngle, rotationAxis);
   mesh->applyTransformation(rotationMatrix);
}

float Cone::computeScalingFactor(QVector3D direction)
{
   return computeBaseSize(maxCellRatio)
          * computeNormalizedMagnitude(direction)
          * Settings::visualization::glyphs().scale;
}
