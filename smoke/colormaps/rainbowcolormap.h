#ifndef RAINBOWCOLORMAP_H
#define RAINBOWCOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include "unused.h"

class RainbowColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap* Create(int numColors, float saturation, float UNUSED(hue));

private:
    float dx;

    RainbowColorMap(int numColors, float saturation, float dx = 0.8);

    void fill();
    QColor toRainbowColor(float i);

};

#endif // RAINBOWCOLORMAP_H
