#include "utilities/approximation.h"
#include "utilities/range.h"

float interpolateBilinearly(QVector2D t, float upperLeft, float upperRight, float lowerLeft, float lowerRight)
{
   assertInUnitRange(t);

   return upperLeft * (1 - t.x()) * (1 - t.y())
          + upperRight * t.x() * (1 - t.y())
          + lowerLeft * (1 - t.x()) * t.y()
          + lowerRight * t.x() * t.y();
}

float interpolateBilinearly(QVector3D position, float upperLeft, float upperRight, float lowerLeft, float lowerRight)
{
   return interpolateBilinearly(position.toVector2D(), upperLeft, upperRight, lowerLeft, lowerRight);
}
