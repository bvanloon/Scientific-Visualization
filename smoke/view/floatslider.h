#ifndef FLOATSLIDER_H
#define FLOATSLIDER_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class FloatSlider;
}

class FloatSlider : public QWidget
{
    Q_OBJECT

public:
    explicit FloatSlider(QWidget *parent = 0);
    ~FloatSlider();

    void init(float minimum, float maximum, float value);
    void setMinimum(float minimum);
    void setMaximum(float maximum);
    void setRange(float minimum, float maximum);
    void setValue(float value);

signals:
    void valueChanged(float value);

private slots:
    void on_slider_sliderMoved(int position);

private:
    Ui::FloatSlider *ui;

    float minimum;
    float maximum;

    void setLabel(QLabel *label, float value);
};

#endif // FLOATSLIDER_H
