#ifndef COLORMAPLEGEND_H
#define COLORMAPLEGEND_H
#include <QResizeEvent>
#include <QWidget>
#include <QRect>
#include <QImage>

#include <colormaps/abstractcolormap.h>
#include <colormaps/rainbowcolormap.h>

namespace Ui {
class ColorMapLegend;
}

class ColorMapLegend : public QWidget
{
    Q_OBJECT

public:
    explicit ColorMapLegend(QWidget *parent = 0);
    ~ColorMapLegend();

public slots:
    void onColorMapChanged(AbstractColorMap colorMapImage);
    void onValueRangeChanged(float minimum, float maximum);
    void onClampRangeChanged(float minimum, float maximum);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::ColorMapLegend *ui;

    QImage colorMapImage;
    float numberOfColors;

    QRect colorBar;

    int numberOfTicks;

    float minimumValue;
    float maximumValue;

    float minimumFactor;
    float maximumFactor;

    static const int colorMapImageWidth;
    static const int tickWidth;
    static const int maximumNumberOfTicks;
    static const QPointF textOffset;

    void drawColorMapImage();
    void drawTicksAndLabels();
    void drawTickandLabel(QPointF left, float value);
    void drawLabel(QPointF left, float labelValue);

    void setFactorRange(float minimum, float maximum);
    void setValueRange(float minimum, float maximum);
    void setColorMap(AbstractColorMap colorMap);

    int getDescriptionLabelHeight();
};

#endif // COLORMAPLEGEND_H
