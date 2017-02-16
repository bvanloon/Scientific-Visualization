#ifndef ABSTRACTCOLORMAP_H
#define ABSTRACTCOLORMAP_H

#include <QImage>

class AbstractColorMap : public QImage
{
public:
    AbstractColorMap(int numColors);

protected:
    int numColors;
};

#endif // ABSTRACTCOLORMAP_H
