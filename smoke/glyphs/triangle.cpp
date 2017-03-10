#include "triangle.h"
#include "settings/visualizationsettings.h"



Triangle::Triangle(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   QVector3D normal = direction.normalized();

   QLineF line = QLineF(0.0f, 0.0f,
                        normal.x(), normal.y());

   //Given is vector dir with units A B C. We need to find a vector x,y,z such that A * x + B * y + C * z = 0.
   //Setting x, z on 1 we find y = -(A * x + C * z) / B with B != 0

   QLineF normalLine = line.normalVector();

   QVector3D orth = QVector3D(normalLine.x2(), normalLine.y2(), 0.0f);

   glyphPoints.append(position + (orth * 5));
   glyphPoints.append(position - (orth * 5));



   glyphPoints.append(position + (normal * direction.length() * 1000));
}
