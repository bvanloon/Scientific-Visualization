#ifndef GRAYSCALECOLORMAP_H
#define GRAYSCALECOLORMAP_H

#include "colormaps/abstractcolormap.h"


class GrayScaleColorMap : public AbstractColorMap
{
public:
    static AbstractColorMap* Create(int numColors);

private:
    GrayScaleColorMap(int numColors);
    void fill();
};

#endif // GRAYSCALECOLORMAP_H
