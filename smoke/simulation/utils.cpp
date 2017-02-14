#include "utils.h"





int cursorLocationToArrayIndex(QPoint newMousePosition, Settings* settings)
{
    // Compute the array index that corresponds to the cursor location
    int xi = (int)clamp((double)(settings->simulation->dimension + 1) * ((double)newMousePosition.x()/ (double)settings->canvas->width));
    int yi = (int)clamp((double)(settings->simulation->dimension + 1) * ((double)newMousePosition.y() / (double)settings->canvas->height));

    //Bound array index to canvas dimensions
    if (xi > (settings->simulation->dimension - 1))
        xi = settings->simulation->dimension - 1;
    if (yi > (settings->simulation->dimension - 1))
        yi = settings->simulation->dimension - 1;
    if (xi < 0)
        xi = 0;
    if (yi < 0)
        yi = 0;

    return yi * settings->simulation->dimension + xi;
}

int clamp(float x){
    return ((x)>=0.0?((int)(x)):(-((int)(1-(x)))));
}

float max(float x, float y)
{
    return x > y ? x : y;
}
