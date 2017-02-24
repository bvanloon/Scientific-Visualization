#ifndef INTSLIDER_H
#define INTSLIDER_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class IntSlider;
}

class IntSlider : public QWidget
{
    Q_OBJECT

public:
    explicit IntSlider(QWidget *parent = 0);
    ~IntSlider();

    void init(int minimum, int maximum, int value);

    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setValue(int value);

private:
    Ui::IntSlider *ui;

    void setLabel(QLabel *label, int value);
};

#endif // INTSLIDER_H
