#include "triangle.h"
#include "settings/visualizationsettings.h"
#include "glyphs/ccwtriangle.h"
#include "utilities/vector.h"

const double Triangle::cellRatio = 0.8;

Triangle::Triangle(QVector3D position, QVector3D direction) :
   AbstractGlyph()
{
   QVector3D orthogonalVector = computeOrthogonalVector(direction);

   double baseSize = this->computeBaseSize(cellRatio);
   double scalingFactor = baseSize * Settings::visualization::glyphs().scale;

   CCWTriangle triangle = CCWTriangle(
               position + (orthogonalVector.normalized() * 0.5 * baseSize),
               position - (orthogonalVector.normalized() * 0.5 * baseSize),
               position + (direction.normalized() * this->computeNormalizedMagnitude(direction) * scalingFactor));

   QVector3D normal = triangle.computeForwardPointingFaceNormal();

   this->addVertices(triangle.getVertices(), normal);
}

GLint Triangle::getDrawMode() const
{
    return GL_TRIANGLES;
}
