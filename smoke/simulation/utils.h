#ifndef UTILS_H
#define UTILS_H

#include "settings/settingsns.h"
#include "settings/simulations.h"

#include <QPoint>

int clamp(float x);
float max(float x, float y);
int cursorLocationToArrayIndex(QPoint newMousePosition);

#endif // UTILS_H
