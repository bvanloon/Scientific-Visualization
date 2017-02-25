#include "utils.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"

int cursorLocationToArrayIndex(QPoint newMousePosition)
{
    // Compute the array index that corresponds to the cursor location
    int xi = (int)clamp((double)(Settings::simulation().dimension + 1) * ((double)newMousePosition.x()/ (double)Settings::canvas().size.width()));
    int yi = (int)clamp((double)(Settings::simulation().dimension + 1) * ((double)newMousePosition.y() / (double)Settings::canvas().size.height()));

    //Bound array index to canvas dimensions
    if (xi > (Settings::simulation().dimension - 1))
        xi = Settings::simulation().dimension - 1;
    if (yi > (Settings::simulation().dimension - 1))
        yi = Settings::simulation().dimension - 1;
    if (xi < 0)
        xi = 0;
    if (yi < 0)
        yi = 0;

    return yi * Settings::simulation().dimension + xi;
}

int clamp(float x){
    return ((x)>=0.0?((int)(x)):(-((int)(1-(x)))));
}

float max(float x, float y)
{
    return x > y ? x : y;
}
