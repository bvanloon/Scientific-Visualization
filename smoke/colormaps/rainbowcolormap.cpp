#include "rainbowcolormap.h"

#include <QDebug>

RainbowColorMap::RainbowColorMap(int numColors, float dx):
    AbstractColorMap(numColors)
{
    qDebug() << "RainbowColorMap";
}

