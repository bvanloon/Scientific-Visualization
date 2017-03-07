#include "abstractcolormap.h"

#include <QDebug>
#include <QColor>

AbstractColorMap::AbstractColorMap(int numColors, float saturation, float hue) :
   QImage(numColors, 1, QImage::Format_ARGB32),
   numColors(numColors),
   saturation(saturation),
   hue(hue)
{
   fill(QColor(Qt::white).rgb());
}


QRgb AbstractColorMap::setSaturation(QColor color, double saturation)
{
   double h, s, v;
   qreal a;

   color.getHsvF(&h, &s, &v, &a);
   color.setHsvF(h, saturation, v, a);
   return color.rgb();
}


int AbstractColorMap::getNumColors()
{
   return numColors;
}
