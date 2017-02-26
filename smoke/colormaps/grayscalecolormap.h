#ifndef GRAYSCALECOLORMAP_H
#define GRAYSCALECOLORMAP_H

#include "colormaps/abstractcolormap.h"


class GrayScaleColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap* Create(int numColors, float saturation);

private:
    GrayScaleColorMap(int numColors, float saturation);
    void fill();
};

#endif // GRAYSCALECOLORMAP_H
