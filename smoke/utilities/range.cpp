#include "range.h"
#include <assert.h>
#include <limits>

void assertInUnitRange(float t)
{
   float epsilon = 100000 * std::numeric_limits<float>::epsilon();

   assert(t >= 0.0f - epsilon && t <= 1.0f + epsilon);
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
