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

private:
    Ui::FloatSlider *ui;
};

#endif // FLOATSLIDER_H
