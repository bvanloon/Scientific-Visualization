#ifndef HEATCOLORMAP_H
#define HEATCOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class HeatColorMap : public AbstractColorMap
{
public:
    HeatColorMap(int numColors, float dx = 0.8);

private:
    void fill();
    QRgb toHeatColor(float f);

    float dx;
};

#endif // HEATCOLORMAP_H
