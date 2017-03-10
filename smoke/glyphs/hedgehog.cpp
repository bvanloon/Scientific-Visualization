#include "hedgehog.h"
#include "settings/visualizationsettings.h"


HedgeHog::HedgeHog(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   glyphPoints.append(position);
   glyphPoints.append((position + (direction * Settings::visualization::glyphs().vectorScale)));
}
