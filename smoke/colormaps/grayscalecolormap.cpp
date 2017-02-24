#include "grayscalecolormap.h"

#include <QDebug>
#include <QImage>
#include <QColor>

GrayScaleColorMap::GrayScaleColorMap(int numColors):
    AbstractColorMap(numColors)

{
    fill();
}

AbstractColorMap *GrayScaleColorMap::Create(int numColors)
{
       return new GrayScaleColorMap(numColors);
}

void GrayScaleColorMap::fill()
{
    float stepSize = 1.0 /(numColors - 1);
    float f = 0;
    //Scale grayscale with 255 (total number of available steps in RGB
    for(int i = 0; i < numColors; f += stepSize * (255), i++){
        setPixel(i, 0, qRgb(f,f,f));
    }
}
