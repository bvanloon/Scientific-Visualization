#include "abstractcolormap.h"

#include <QDebug>

AbstractColorMap::AbstractColorMap(int numColors):
    numColors(numColors)
{
    qDebug() << "AbstractColorMap";
}

