#ifndef COLORMAPLEGEND_H
#define COLORMAPLEGEND_H
#include <QResizeEvent>
#include <QWidget>
#include <QRect>

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
    void onColorMapChanged(AbstractColorMap colorMap);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::ColorMapLegend *ui;

    AbstractColorMap* colorMap;

    QRect colorBar;

    int numberOfTicks;

    static const int colorMapImageWidth;
    static const int tickWidth;
    static const int maximumNumberOfTicks;

    void drawColorMapImage();
    void drawLabels();
    void drawLabel();
    void drawTicks();
    void drawTick(QPointF left);
};

#endif // COLORMAPLEGEND_H
