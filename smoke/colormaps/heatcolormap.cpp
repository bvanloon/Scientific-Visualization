#include "heatcolormap.h"

#include <math.h>

#include <QDebug>


AbstractColorMap *HeatColorMap::Create(int numColors, float saturation, float hue = no_hue)
{
   return new HeatColorMap(numColors, saturation);
}


HeatColorMap::HeatColorMap(int numColors, float saturation) :
   AbstractColorMap(numColors, saturation)
{
   fill();
}


void HeatColorMap::fill()
{
   float stepSize = 1.0 / (numColors - 1);
   float f = 0;

   for (int i = 0; i < numColors; f += stepSize, i++)
   {
      setPixel(i, 0, setSaturation(toHeatColor(f), saturation));
   }
}


QRgb HeatColorMap::toHeatColor(float f)
{
   float color_slope = 1.0f / 0.4f * f;
   float red = fmin(1.0f, color_slope);
   float green = fmin(1.0f, color_slope - red);
   float blue = fmax(0.0f, 2.0f * (color_slope - red - green));
   float scale = 255;

   return qRgb(red * scale, green * scale, blue * scale);
}
