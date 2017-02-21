#include "floatslider.h"
#include "ui_floatslider.h"

FloatSlider::FloatSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatSlider)
{
    ui->setupUi(this);

    this->slider = this->ui->slider;
}

FloatSlider::~FloatSlider()
{
    delete ui;
}

void FloatSlider::init(float minimum, float maximum, int numSteps)
{
    this->setMinimum(minimum);
    this->setMaximum(maximum);
    this->numSteps = numSteps;
    this->slider->setRange(0, maximum * numSteps);
}

void FloatSlider::setRange(float minimum, float maximum)
{
    this->setMinimum(minimum);
    this->setMaximum(maximum);
}

void FloatSlider::setMinimum(float minimum)
{
    this->minimumValue = minimum;
    setLabelText(this->ui->minimumLabel, minimum);
}

void FloatSlider::setMaximum(float maximum)
{
    this->maximumValue = maximum;
    setLabelText(this->ui->maximumLabel, maximum);
    this->slider->setMaximum(maximum * numSteps);
}

void FloatSlider::setValue(float value)
{
    this->ui->slider->setValue(mapToIntRange(value));
    this->ui->valueLabel->setText(QString::number(value, 'f', 2));
}

void FloatSlider::setValue(int value)
{
    setValue(mapToFloatRange(value));
}

void FloatSlider::setDisabled(bool disabled)
{
    this->ui->slider->setDisabled(disabled);
    this->ui->minimumLabel->setDisabled(disabled);
    this->ui->maximumLabel->setDisabled(disabled);
    this->ui->valueLabel->setDisabled(disabled);
}

float FloatSlider::minimum() const
{
    return this->minimumValue;
}

float FloatSlider::maximum() const
{
    return this->maximumValue;
}

float FloatSlider::value() const
{
    return mapToFloatRange(this->ui->slider->value());
}

float FloatSlider::mapToFloatRange(int value) const
{
    float slope = (maximumValue - minimumValue) / ((float) slider->maximum() - slider->minimum());
    return minimumValue + slope * (value - slider->minimum());
}


int FloatSlider::mapToIntRange(float value) const
{
    float slope = ((float) slider->maximum() - slider->minimum()) / (maximumValue - minimumValue);
    return qRound(slider->minimum() + slope * (value - maximumValue));
}

void FloatSlider::setLabelText(QLabel *label, float value)
{
    label->setText(QString::number(value, 'f', 2));
}

void FloatSlider::on_slider_sliderMoved(int position)
{
    this->setValue(position);
    qDebug() << "Do stuff! Emit a signal for example?";
}
