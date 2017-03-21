#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QVector2D>
#include <QVector3D>

float interpolateBilinearly(QVector2D position, float upperLeft, float upperRight, float lowerLeft, float lowerRight);

float interpolateBilinearly(QVector3D position, float upperLeft, float upperRight, float lowerLeft, float lowerRight);

#endif // INTERPOLATION_H
