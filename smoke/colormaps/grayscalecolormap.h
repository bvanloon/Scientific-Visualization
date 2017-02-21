#ifndef GRAYSCALECOLORMAP_H
#define GRAYSCALECOLORMAP_H

#include "colormaps/abstractcolormap.h"
#include <QRgb>

class GrayScaleColorMap : public AbstractColorMap
{
public:
    GrayScaleColorMap(int numColors);

private:
    void fill();
};

#endif // GRAYSCALECOLORMAP_H
