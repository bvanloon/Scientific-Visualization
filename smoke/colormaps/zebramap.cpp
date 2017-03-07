#include "zebramap.h"

#include <QDebug>

ZebraMap::ZebraMap(int numColors, float saturation):
    AbstractColorMap(numColors, saturation)

{
    fill();
}

AbstractColorMap *ZebraMap::Create(int numColors, float saturation, float hue = no_hue)
{
       return new ZebraMap(numColors, saturation);
}

void ZebraMap::fill()
{

    //Scale grayscale with 255 (total number of available steps in RGB
    for(int i = 0; i < numColors; i +=2 ){
        setPixel(i, 0, qRgb(1,1,1));
    }
}
