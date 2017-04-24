#include "grayscalecolormap.h"

GrayScaleColorMap::GrayScaleColorMap(int numColors, float saturation) :
   AbstractColorMap(numColors, saturation)

{
   fill();
}

AbstractColorMap *GrayScaleColorMap::Create(int numColors, float saturation, float UNUSED(hue))
{
   return new GrayScaleColorMap(numColors, saturation);
}

void GrayScaleColorMap::fill()
{
   float stepSize = 1.0 / (numColors - 1);
   float f = 0;

   //Scale grayscale with 255 (total number of available steps in RGB
   for (int i = 0; i < numColors; f += stepSize * 255, i++)
   {
      setPixel(i, 0, qRgb(f, f, f));
   }
}
