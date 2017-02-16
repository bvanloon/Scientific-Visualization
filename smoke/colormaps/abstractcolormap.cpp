#include "abstractcolormap.h"

#include <QDebug>
#include <QColor>

AbstractColorMap::AbstractColorMap(int numColors):
    numColors(numColors),
    QImage(1, numColors, QImage::Format_ARGB32)
{
    fill(QColor(Qt::white).rgb());
}

int AbstractColorMap::getNumColors()
{
    return numColors;
}
