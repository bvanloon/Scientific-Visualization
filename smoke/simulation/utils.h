#ifndef UTILS_H
#define UTILS_H

#include "settings/settings.h"
#include <QPoint>

int clamp(float x);
float max(float x, float y);
int cursorLocationToArrayIndex(QPoint newMousePosition, Settings* settings);

#endif // UTILS_H
