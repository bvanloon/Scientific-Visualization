#include "huecolormap.h"

HueColorMap::HueColorMap(int numColors, float saturation, float hue) :
   AbstractColorMap(numColors, saturation, hue)
{
   fill();
}


AbstractColorMap *HueColorMap::Create(int numColors, float saturation, float hue)
{
   return new HueColorMap(numColors, saturation, hue);
}


void HueColorMap::fill()
{
   float stepSize = 0.9f / (numColors - 1);
   float f = 0.1f * 255;

   for (int i = 0; i < numColors; f += stepSize * 255, i++)
   {
      QColor color = qRgb(f, f, f);
      double h, s, v;
      qreal a;
      color.getHsvF(&h, &s, &v, &a);
      color.setHsvF(hue, saturation, v, a);
      setPixel(i, 0, color.rgb());
   }
}
