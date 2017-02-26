#ifndef RAINBOWCOLORMAP_H
#define RAINBOWCOLORMAP_H

#include "colormaps/abstractcolormap.h"

class RainbowColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap* Create(int numColors, float saturation);

private:
    float dx;

    RainbowColorMap(int numColors, float saturation, float dx = 0.8);

    void fill();
    QColor toRainbowColor(float i);

};

#endif // RAINBOWCOLORMAP_H
