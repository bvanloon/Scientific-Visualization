#include "rainbowcolormap.h"

#include <math.h>

#include <QDebug>
#include <QImage>
#include <QColor>

RainbowColorMap::RainbowColorMap(int numColors, float dx):
    AbstractColorMap(numColors),
    dx(dx)
{ 
    fill();
}


void RainbowColorMap::fill()
{
    float stepSize = 1.0/(numColors - 1);
    float f = 0;
    for(int i = 0; i < numColors; f+=stepSize, i++){
        setPixel(i, 0, toRainbowColor(f));
    }
}

QRgb RainbowColorMap::toRainbowColor(float f)
{
    float g = (6 - 2 * dx) * f + dx;
    int red = fmax(0, (3 - fabs(g - 4) - fabs(g - 5)) / 2.0) * 255;
    int green = fmax(0, (4 - fabs(g - 2) - fabs(g - 4)) / 2.0) * 255;
    int blue = fmax(0, (3 - fabs(g - 1) - fabs(g - 2)) / 2.0) * 255;
    return qRgb(red, green, blue);
}



