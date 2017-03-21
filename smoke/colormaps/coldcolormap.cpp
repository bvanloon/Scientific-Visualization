#include "coldcolormap.h"


#include <math.h>

#include <QDebug>


AbstractColorMap *Coldcolormap::Create(int numColors, float saturation, float UNUSED(hue))
{
   return new Coldcolormap(numColors, saturation);
}


Coldcolormap::Coldcolormap(int numColors, float saturation) :
   AbstractColorMap(numColors, saturation)
{
   fill();
}


void Coldcolormap::fill()
{
   float stepSize = 1.0 / (numColors - 1);
   float f = 0;

   for (int i = 0; i < numColors; f += stepSize, i++)
   {
      setPixel(i, 0, setSaturation(toColdColor(f), saturation));
   }
}


QRgb Coldcolormap::toColdColor(float f)
{
   float color_slope = 1.0f / 0.4f * f;
   float blue = fmin(1.0f, color_slope);
   float green = fmin(1.0f, color_slope - blue);
   float red = fmax(0.0f, 2.0f * (color_slope - blue - green));
   float scale = 255;

   return qRgb(red * scale, green * scale, blue * scale);
}
