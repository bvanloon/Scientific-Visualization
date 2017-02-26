#ifndef ABSTRACTCOLORMAP_H
#define ABSTRACTCOLORMAP_H

#include <QImage>
#include <QColor>
#include <QRgb>

class AbstractColorMap : public QImage
{
public:
    int getNumColors();
    static AbstractColorMap * Create(int numColors, float saturation);
    AbstractColorMap(int numColors = 256, float saturation = 1.0f);

protected:
    int numColors;
    float saturation;
    QRgb setSaturation(QColor color, double saturation);
};

#endif // ABSTRACTCOLORMAP_H
