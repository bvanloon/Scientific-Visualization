#ifndef INTSLIDER_H
#define INTSLIDER_H

#include <QWidget>

namespace Ui {
class IntSlider;
}

class IntSlider : public QWidget
{
    Q_OBJECT

public:
    explicit IntSlider(QWidget *parent = 0);
    ~IntSlider();

private:
    Ui::IntSlider *ui;
};

#endif // INTSLIDER_H
