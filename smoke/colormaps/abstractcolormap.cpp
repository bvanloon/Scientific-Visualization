#include "abstractcolormap.h"

#include <QDebug>
#include <QColor>

AbstractColorMap::AbstractColorMap(int numColors):
    QImage(numColors, 1, QImage::Format_ARGB32),
    numColors(numColors)
{
    fill(QColor(Qt::white).rgb());
}

QRgb AbstractColorMap::setSaturation(QColor color, double saturation)
{


    qDebug() <<  color;

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
