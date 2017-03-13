#include "hedgehog.h"
#include "settings/visualizationsettings.h"


HedgeHog::HedgeHog(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   QVector3D offSet = computeOffSet(direction);
   QVector3D normal = computeNormal(direction);

   addVertex(position, normal);
   addVertex(position + offSet, normal);
}

QVector3D HedgeHog::computeNormal(QVector3D direction)
{
   QVector3D normalDirection = direction.normalized();

   QLineF directionLine = QLineF(0.0f, 0.0f,
                         normalDirection.x(), normalDirection.y());

   QLineF normalLine = directionLine.normalVector();

   return QVector3D(normalLine.x2(), normalLine.y2(), 0.0f);
}

QVector3D HedgeHog::computeOffSet(QVector3D direction)
{
   return(direction * Settings::visualization::glyphs().vectorScale);
}
