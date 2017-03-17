#include "cone.h"
#include "settings/visualizationsettings.h"
#include "shapes/cone.h"
#include <QMatrix4x4>
#include <QDebug>
#include <math.h>

const double Cone::maxCellRatio = 2.0;

Cone::Cone(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar),
   mesh(::shapes::Cone().toTriangleMesh()),
   normalizedMagnitude(computeNormalizedMagnitude(direction)),
   position(position),
   normalizedDirection(direction.normalized())
{
   transform();
   this->addVertices(this->mesh->getVerticesAsVBO(), this->mesh->getNormalsAsVBO());
}

void Cone::transform()
{
   QMatrix4x4 transformationMatrix = translationMatrix() * rotationMatrix() * scalingMatrix();

   this->mesh->applyTransformation(transformationMatrix);
}

QMatrix4x4 Cone::translationMatrix()
{
   QMatrix4x4 translationMatrix;

   translationMatrix.translate(this->position);
   return translationMatrix;
}

QMatrix4x4 Cone::scalingMatrix()
{
   float scalingFactor = computeScalingFactor();
   QMatrix4x4 scalingMatrix;

   scalingMatrix.scale(scalingFactor);
   return scalingMatrix;
}

QMatrix4x4 Cone::rotationMatrix()
{
   //http://stackoverflow.com/questions/20177506/rotate-geometry-to-align-to-a-direction-vector
   //http://tonyobryan.com/index.php?article=28
   QVector3D rotationAxis = QVector3D::crossProduct(shapes::Cone::getDefaultDirection(), this->normalizedDirection);
   float rotationAngle = radiansToDegrees(acos(QVector3D::dotProduct(rotationAxis.normalized(), this->normalizedDirection)));
   QMatrix4x4 rotationMatrix;

   rotationMatrix.rotate(rotationAngle, rotationAxis);
   return rotationMatrix;
}

float Cone::computeScalingFactor()
{
   return computeBaseSize(maxCellRatio)
          * normalizedMagnitude
          * Settings::visualization::glyphs().scale;
}

float Cone::radiansToDegrees(float radians)
{
   return radians * 180 / M_PI;
}
