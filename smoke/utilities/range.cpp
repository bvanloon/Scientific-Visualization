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

float ensureUnitRange(float t)
{
   float epsilon = std::numeric_limits<float>::epsilon();

   if ((t < 0.0f) && ((t + epsilon) >= 0.0f)) return 0.0f;

   if ((t > 1.0f) && ((t - epsilon) <= 1.0f)) return 1.0f;

   assertInUnitRange(t);
   return t;
}

QVector2D ensureUnitRange(QVector2D vector)
{
   float epsilon = std::numeric_limits<float>::epsilon();

   vector.setX(ensureUnitRange(vector.x()));
   vector.setY(ensureUnitRange(vector.y()));
   assertInUnitRange(vector);
   return vector;
}

QVector3D ensureUnitRange(QVector3D vector)
{
   float epsilon = std::numeric_limits<float>::epsilon();

   vector.setX(ensureUnitRange(vector.x()));
   vector.setY(ensureUnitRange(vector.y()));
   vector.setZ(ensureUnitRange(vector.z()));
   assertInUnitRange(vector);
   return vector;
}
