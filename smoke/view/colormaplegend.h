#ifndef COLORMAPLEGEND_H
#define COLORMAPLEGEND_H
#include <QResizeEvent>
#include <QWidget>
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

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::ColorMapLegend *ui;

    AbstractColorMap* colorMap;

    static const int colorMapImageWidth;

    void draw();
    void drawColorMapImage();
};

#endif // COLORMAPLEGEND_H
