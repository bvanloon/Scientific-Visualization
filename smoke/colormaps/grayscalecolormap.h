#ifndef GRAYSCALECOLORMAP_H
#define GRAYSCALECOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class GrayScaleColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap* Create(int numColors);

private:
    GrayScaleColorMap(int numColors);
    void fill();
};

#endif // GRAYSCALECOLORMAP_H
