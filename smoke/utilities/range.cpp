#include "range.h"
#include <assert.h>

void inUnitRange(float t)
{
   assert(t >= 0 && t <= 1);
}

void inUnitRange(QVector2D t)
{
   inUnitRange(t.x());
   inUnitRange(t.y());
}

void inUnitRange(QVector3D t)
{
   inUnitRange(t.x());
   inUnitRange(t.y());
   inUnitRange(t.z());
}
