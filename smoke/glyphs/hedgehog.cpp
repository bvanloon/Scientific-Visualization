#include "hedgehog.h"
#include "settings/visualizationsettings.h"

const double HedgeHog::cellRatio = 1;

HedgeHog::HedgeHog(QVector3D position, QVector3D direction) :
   AbstractGlyph()
{
   build(position, direction);
}

GLint HedgeHog::getDrawMode() const
{
   return GL_LINES;
}

void HedgeHog::build(QVector3D position, QVector3D direction)
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
   return(direction.normalized() * Settings::visualization::glyphs().scale * computeNormalizedMagnitude(direction) * computeBaseSize(cellRatio));
}
