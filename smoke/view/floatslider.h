#ifndef FLOATSLIDER_H
#define FLOATSLIDER_H

#include <QWidget>

namespace Ui {
class FloatSlider;
}

class FloatSlider : public QWidget
{
    Q_OBJECT

public:
    explicit FloatSlider(QWidget *parent = 0);
    ~FloatSlider();

    void init(int numSteps = 100, float minimum, float maximum);

private:
    Ui::FloatSlider *ui;

    int numSteps;
    float minimum;
    float maximum;
};

#endif // FLOATSLIDER_H
