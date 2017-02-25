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

    int value() const;

    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setValue(int value);

signals:
    void valueChanged(int value);

private slots:
    void on_slider_valueChanged(int position);

private:
    Ui::IntSlider *ui;

    void setLabel(QLabel *label, int value);
};

#endif // INTSLIDER_H
