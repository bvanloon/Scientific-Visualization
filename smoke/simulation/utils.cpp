#include "utils.h"




int cursorLocationToArrayIndex(QPoint newMousePosition, const settingsns::Simulation& simulationSettings, Settings* settings)
{
    // Compute the array index that corresponds to the cursor location
    int xi = (int)clamp((double)(simulationSettings.dimension + 1) * ((double)newMousePosition.x()/ (double)settings->canvas->width));
    int yi = (int)clamp((double)(simulationSettings.dimension + 1) * ((double)newMousePosition.y() / (double)settings->canvas->height));

    //Bound array index to canvas dimensions
    if (xi > (simulationSettings.dimension - 1))
        xi = simulationSettings.dimension - 1;
    if (yi > (simulationSettings.dimension - 1))
        yi = simulationSettings.dimension - 1;
    if (xi < 0)
        xi = 0;
    if (yi < 0)
        yi = 0;

    return yi * simulationSettings.dimension + xi;
}

int clamp(float x){
    return ((x)>=0.0?((int)(x)):(-((int)(1-(x)))));
}

float max(float x, float y)
{
    return x > y ? x : y;
}
