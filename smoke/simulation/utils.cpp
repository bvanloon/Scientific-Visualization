#include "utils.h"

#include "settings/settingsns.h"
#include "settings/simulations.h"
#include "settings/canvass.h"

int cursorLocationToArrayIndex(QPoint newMousePosition)
{
    // Compute the array index that corresponds to the cursor location
    int xi = (int)clamp((double)(settingsns::simulation().dimension + 1) * ((double)newMousePosition.x()/ (double)settingsns::canvas().size.width()));
    int yi = (int)clamp((double)(settingsns::simulation().dimension + 1) * ((double)newMousePosition.y() / (double)settingsns::canvas().size.height()));

    //Bound array index to canvas dimensions
    if (xi > (settingsns::simulation().dimension - 1))
        xi = settingsns::simulation().dimension - 1;
    if (yi > (settingsns::simulation().dimension - 1))
        yi = settingsns::simulation().dimension - 1;
    if (xi < 0)
        xi = 0;
    if (yi < 0)
        yi = 0;

    return yi * settingsns::simulation().dimension + xi;
}

int clamp(float x){
    return ((x)>=0.0?((int)(x)):(-((int)(1-(x)))));
}

float max(float x, float y)
{
    return x > y ? x : y;
}
