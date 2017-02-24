#ifndef RAINBOWCOLORMAP_H
#define RAINBOWCOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class RainbowColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap* Create(int numColors);

private:

    RainbowColorMap(int numColors, float dx = 0.8);

    void fill();
    QRgb toRainbowColor(float i);

    float dx;
};

#endif // RAINBOWCOLORMAP_H
