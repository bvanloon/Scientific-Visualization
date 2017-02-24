#include "abstractcolormap.h"

#include <QDebug>


AbstractColorMap::AbstractColorMap(int numColors):
    QImage(numColors, 1, QImage::Format_ARGB32),
    numColors(numColors)
{
    fill(QColor(Qt::white).rgb());
}

int AbstractColorMap::getNumColors()
{
    return numColors;
}
