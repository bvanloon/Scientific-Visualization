#include "triangle.h"
#include "settings/visualizationsettings.h"
#include "glyphs/ccwtriangle.h"

Triangle::Triangle(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   QVector3D orthogonalVector = computeOrthogonalVector(direction);

   CCWTriangle triangle = CCWTriangle(
               position + (orthogonalVector * 5),
               position - (orthogonalVector * 5),
               position + (direction.normalized() * direction.length() * 1000));

   QVector3D normal = triangle.computeForwardPointingFaceNormal();

   this->addVertex(triangle.getA(), normal);
   this->addVertex(triangle.getB(), normal);
   this->addVertex(triangle.getC(), normal);
}

QVector3D Triangle::computeOrthogonalVector(QVector3D vector)
{
   QVector3D normalVector = vector.normalized();
   QLineF line = QLineF(0.0f, 0.0f,
                         normalVector.x(), normalVector.y());
   QLineF normalLine = line.normalVector();

   return QVector3D(normalLine.x2(), normalLine.y2(), 0.0f);
}
