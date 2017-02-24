#ifndef ABSTRACTCOLORMAP_H
#define ABSTRACTCOLORMAP_H

#include <QImage>
#include <QColor>
#include <QRgb>

class AbstractColorMap : public QImage
{
public:
    int getNumColors();
    static AbstractColorMap * Create(int numColors);
    AbstractColorMap(int numColors = 256);

protected:
    int numColors;

    QRgb setSaturation(QColor color, double saturation);
};

#endif // ABSTRACTCOLORMAP_H
