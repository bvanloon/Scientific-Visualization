#include "triangle.h"
#include "settings/visualizationsettings.h"
#include "glyphs/ccwtriangle.h"
#include "utilities/vector.h"

Triangle::Triangle(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   QVector3D orthogonalVector = computeOrthogonalVector(direction);

   CCWTriangle triangle = CCWTriangle(
               position + (orthogonalVector * 5),
               position - (orthogonalVector * 5),
               position + (direction.normalized() * direction.length() * Settings::visualization::glyphs().vectorScale));

   QVector3D normal = triangle.computeForwardPointingFaceNormal();

   this->addVertices(triangle.getVertices(), normal);
}
