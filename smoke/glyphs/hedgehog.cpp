#include "hedgehog.h"
#include "settings/visualizationsettings.h"


HedgeHog::HedgeHog(QVector3D position, QVector3D direction, float scalar) :
   AbstractGlyph(scalar)
{
   vertices.append(position);
   vertices.append((position + (direction * Settings::visualization::glyphs().vectorScale)));
}
