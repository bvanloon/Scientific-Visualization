#include "range.h"
#include <assert.h>
#include <limits>

void assertInUnitRange(float t)
{
   assert(t >= 0.0f && t <= 1.0f);
}

void assertInUnitRange(QVector2D t)
{
   assertInUnitRange(t.x());
   assertInUnitRange(t.y());
}

void assertInUnitRange(QVector3D t)
{
   assertInUnitRange(t.x());
   assertInUnitRange(t.y());
   assertInUnitRange(t.z());
}
