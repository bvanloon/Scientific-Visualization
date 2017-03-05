#include "utilities.h"
#include <assert.h>

void inUnitRange(float t){
    assert(t >= 0 && t <= 1);
}

void inUnitRange(QVector2D t){
    inUnitRange(t.x());
    inUnitRange(t.y());
}

void inUnitRange(QVector3D t){
    inUnitRange(t.x());
    inUnitRange(t.y());
    inUnitRange(t.z());
}

float interpolateBilinearly(QVector2D t, float upperLeft, float upperRight, float lowerLeft, float lowerRight){
    inUnitRange(t);

    return upperLeft * (1 - t.x()) * ( 1 - t.y())
            + upperRight * t.x() * (1 - t.y())
            + lowerLeft * (1 - t.x()) * t.y()
            + lowerRight * t.x() * t.y();
}

float interpolateBilinearly(QVector3D position, float upperLeft, float upperRight, float lowerLeft, float lowerRight)
{
    return interpolateBilinearly(position.toVector2D(), upperLeft, upperRight, lowerLeft, lowerRight);
}
