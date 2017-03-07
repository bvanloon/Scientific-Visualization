#ifndef ABSTRACTCOLORMAP_H
#define ABSTRACTCOLORMAP_H

#include <QImage>
#include <QColor>
#include <QRgb>

#define no_hue -1.0f
class AbstractColorMap : public QImage
{
public:
    int getNumColors();
    static AbstractColorMap * Create(int numColors, float saturation, float hue = no_hue);
    AbstractColorMap(int numColors = 256, float saturation = 1.0f, float hue = no_hue);

protected:
    int numColors;
    float saturation;
    float hue;
    QRgb setSaturation(QColor color, double saturation);
};

#endif // ABSTRACTCOLORMAP_H
