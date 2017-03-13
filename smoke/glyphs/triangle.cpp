#include "triangle.h"
#include "settings/visualizationsettings.h"

Triangle::Triangle(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   QVector3D orthogonalVector = computeOrthogonalVector(direction);

   vertices.append(position + (orthogonalVector * 5));
   vertices.append(position - (orthogonalVector * 5));
   vertices.append(position + (direction.normalized() * direction.length() * 1000));
}

QVector3D Triangle::computeOrthogonalVector(QVector3D vector)
{
   QVector3D normalVector = vector.normalized();
   QLineF line = QLineF(0.0f, 0.0f,
                         normalVector.x(), normalVector.y());
   //Given is vector dir with units A B C. We need to find a vector x,y,z such that A * x + B * y + C * z = 0.
   //Setting x, z on 1 we find y = -(A * x + C * z) / B with B != 0
   QLineF normalLine = line.normalVector();

   return QVector3D(normalLine.x2(), normalLine.y2(), 0.0f);
}
