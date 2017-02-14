#include "abstractcolormap.h"

#include <QDebug>

AbstractColorMap::AbstractColorMap(int numColors):
    numColors(numColors),
    image(new QImage(1, numColors, QImage::Format_ARGB32))
{
    qDebug() << "AbstractColorMap";
}
