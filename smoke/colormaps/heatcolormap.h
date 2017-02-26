#ifndef HEATCOLORMAP_H
#define HEATCOLORMAP_H

#include "colormaps/abstractcolormap.h"

class HeatColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap * Create(int numColors, float saturation);

private:
    HeatColorMap(int numColors, float saturation);

    void fill();
    QRgb toHeatColor(float f);
};

#endif // HEATCOLORMAP_H
