#include "diverging.h"
#include <qdebug.h>
AbstractColorMap *Diverging::Create(int numColors, float saturation, float UNUSED(hue))
{
   return new Diverging(numColors, saturation);
}

Diverging::Diverging(int numColors, float saturation) :
   AbstractColorMap(numColors, saturation)
{
   fill();
}

void Diverging::fill()
{
   float stepSize = 1.0 / ((numColors - 1) / 2.0);
   float f = 0.0;
   float fmid = stepSize * (numColors - 1) / 2.0;

   for (int i = 0; i < numColors; f += stepSize, i++)
   {
      setPixel(i, 0, setSaturation(divergenceColor(f, fmid), saturation));
   }
}

QColor Diverging::divergenceColor(float f, float fmid)
{
   float rMin = 0.230 * 255.0;
   float rMid = 0.865 * 255.0;
   float rMax = 0.706 * 255.0;

   float gMin = 0.299 * 255.0;
   float gMid = 0.865 * 255.0;
   float gMax = 0.016 * 255.0;

   float bMin = 0.754 * 255.0;
   float bMid = 0.865 * 255.0;
   float bMax = 0.150 * 255.0;

   int red, green, blue;
   if (f <= fmid)
   {
      red = rMin + ((rMid - rMin) * f);
      green = gMin + ((gMid - gMin) * f);
      blue = bMin + ((bMid - bMin) * f);
   }
   else
   {
      red = rMid + ((rMax - rMid) * (f / 2.0));
      green = gMid + ((gMax - gMid) * (f / 2.0));
      blue = bMid + ((bMax - bMid) * (f / 2.0));
   }

   if ((red < 0) || (green < 0) || (blue < 0) || (red > 255) || (green > 255) || (blue > 255))
   {
      qDebug() << "paniek";
   }
   return QColor(red, green, blue);
}
