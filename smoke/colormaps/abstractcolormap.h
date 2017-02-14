#ifndef ABSTRACTCOLORMAP_H
#define ABSTRACTCOLORMAP_H

#include <QImage>

class AbstractColorMap
{
public:
    AbstractColorMap(int numColors);

protected:
    int numColors;

    QImage* image;

};

#endif // ABSTRACTCOLORMAP_H
