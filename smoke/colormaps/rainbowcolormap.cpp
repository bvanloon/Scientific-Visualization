#include "rainbowcolormap.h"

#include <math.h>

#include <QDebug>
#include <QImage>

RainbowColorMap::RainbowColorMap(int numColors, float dx):
    AbstractColorMap(numColors),
    dx(dx)
{
    fillImage();
}

QImage* RainbowColorMap::getImage()
{
    return this->image;
}

void RainbowColorMap::fillImage()
{
    float stepSize = 1.0/(numColors - 1);
    for(float i = 0; i < numColors; i+=stepSize){
        this->image->setPixel(0, i, toRainbowColor(i));
    }
}

QRgb RainbowColorMap::toRainbowColor(float f)
{
    float g = (6 - 2 * dx) * f + dx;
    int red = fmax(0, (3 - fabs(g - 4) - fabs(g - 5)) / 2.0) * 256;
    int green = fmax(0, (4 - fabs(g - 2) - fabs(g - 4)) / 2.0) * 256;
    int blue = fmax(0, (3 - fabs(g - 1) - fabs(g - 2)) / 2.0) * 256;
    return qRgb(red, green, blue);
}



