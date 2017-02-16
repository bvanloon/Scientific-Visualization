#ifndef COLORMAPLEGEND_H
#define COLORMAPLEGEND_H

#include <QWidget>

namespace Ui {
class ColorMapLegend;
}

class ColorMapLegend : public QWidget
{
    Q_OBJECT

public:
    explicit ColorMapLegend(QWidget *parent = 0);
    ~ColorMapLegend();

private:
    Ui::ColorMapLegend *ui;
};

#endif // COLORMAPLEGEND_H
