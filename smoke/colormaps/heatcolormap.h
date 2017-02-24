#ifndef HEATCOLORMAP_H
#define HEATCOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class HeatColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap * Create(int numColors);

private:
    HeatColorMap(int numColors);

    void fill();
    QRgb toHeatColor(float f);

    float dx;
};

#endif // HEATCOLORMAP_H
