#include "twocolorcolormap.h"


AbstractColorMap *TwoColorColormap::Create(int numColors, float saturation, float UNUSED(hue))
{
   return new TwoColorColormap(numColors, saturation);
}

TwoColorColormap::TwoColorColormap(int numColors, float saturation) :
   AbstractColorMap(numColors, saturation)
{
   fill();
}

void TwoColorColormap::fill()
{
   float stepSize = 1.0 / (numColors - 1);
   float f = 0;

   for (int i = 0; i < numColors; f += stepSize, i++)
   {
      setPixel(i, 0, toColor(f));
   }
}

QRgb TwoColorColormap::toColor(float f)
{
   //R: 23 G: 156 B: 194
   //    R: 206 G: 128 B: 92
   int red = 23.0 + (246.0 - 23.0) * f;
   int green = 156.0 + (118.0 - 156.0) * f;
   int blue = 194.0 + (82.0 - 194.0) * f;



   return qRgb(red, green, blue);
}
