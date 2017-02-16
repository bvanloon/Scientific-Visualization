#ifndef RAINBOWCOLORMAP_H
#define RAINBOWCOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class RainbowColorMap : public AbstractColorMap
{
public:
    RainbowColorMap(int numColors, float dx);

private:
    void fill();
    QRgb toRainbowColor(float i);

    float dx;
};

#endif // RAINBOWCOLORMAP_H
