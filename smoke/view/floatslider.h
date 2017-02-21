#ifndef FLOATSLIDER_H
#define FLOATSLIDER_H

#include <QWidget>
#include <QSlider>
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

    void init(float minimumValue = 0.0f, float maximumValue = 1.0f, int numSteps = 100);

    void setRange(float minimumValue, float maximumValue);
    void setMinimum(float minimum);
    void setMaximum(float maximum);
    void setValue(float value);
    void setDisabled(bool disabled);

    float minimum() const;
    float maximum() const;
    float value() const;

signals:
    void sliderMoved(float value);

private:
    Ui::FloatSlider *ui;

    float mapToFloatRange(int value) const;
    int mapToIntRange(float value) const;

    QSlider* slider;

    void setLabelText(QLabel *label, float value);

    int numSteps;
    float minimumValue;
    float maximumValue;
};

#endif // FLOATSLIDER_H
