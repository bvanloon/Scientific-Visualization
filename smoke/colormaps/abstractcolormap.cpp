#include "abstractcolormap.h"

#include <QDebug>
#include <QColor>

AbstractColorMap::AbstractColorMap(int numColors):
    numColors(numColors),
    image(new QImage(1, numColors, QImage::Format_ARGB32))
{
    this->image->fill(QColor(Qt::white).rgb());
}
