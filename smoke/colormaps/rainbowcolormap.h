#ifndef RAINBOWCOLORMAP_H
#define RAINBOWCOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class RainbowColorMap : public AbstractColorMap
{
public:
    RainbowColorMap(int numColors, float dx = 0.8);

private:
    void fill();
    QRgb toRainbowColor(float i);

    float dx;
};

#endif // RAINBOWCOLORMAP_H
