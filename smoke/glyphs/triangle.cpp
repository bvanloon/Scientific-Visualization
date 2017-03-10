#include "triangle.h"
#include "settings/visualizationsettings.h"



Triangle::Triangle(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   QVector3D normal = direction.normalized();

   //Given is vector dir with units A B C. We need to find a vector x,y,z such that A * x + B * y + C * z = 0.
   //Setting x, z on 1 we find y = -(A * x + C * z) / B with B != 0
   QVector3D orth;

   if (direction.y() != 0)
   {
      float x = 1.0f;

      float z = 1.0f;

      float y = -(direction.x() * x + direction.z() * z);
      orth = QVector3D(x, y, z);
   }/*
     * else if (direction.x() != 0)
     * {
     * float y = 1.0f;
     *
     * float z = 1.0f;
     *
     * float x = -(direction.y() * y + direction.z() * z);
     * orth = QVector3D(x, y, z);
     * }
     * else
     * {
     * orth = QVector3D(0.0, 0.0, 0.0);
     * }*/

   orth.normalized();


   glyphPoints.append(position - (orth * Settings::visualization::glyphs().vectorScale));

   glyphPoints.append(position + (orth * Settings::visualization::glyphs().vectorScale));
   glyphPoints.append(position + (normal * Settings::visualization::glyphs().vectorScale));
}
