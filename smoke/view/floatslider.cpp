#include "floatslider.h"
#include "ui_floatslider.h"

#include <QString>
#include "utilities.h"

FloatSlider::FloatSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatSlider)
{
    ui->setupUi(this);
}

FloatSlider::~FloatSlider()
{
    delete ui;
}

void FloatSlider::init(float minimum, float maximum, float value)
{
    setMinimum(minimum);
    setMaximum(maximum);
    setValue(value);
}

void FloatSlider::setMinimum(float minimum)
{
    this->minimum = minimum;
    this->setLabel(this->ui->minimumLabel, minimum);
}

void FloatSlider::setMaximum(float maximum)
{
    this->maximum= maximum;
    this->setLabel(this->ui->maximumLabel, maximum);
}

void FloatSlider::setRange(float minimum, float maximum)
{
    this->setMinimum(minimum);
    this->setMaximum(maximum);
}

void FloatSlider::setValue(float value)
{
    this->setLabel(this->ui->valueLabel, value);
    int position = qRound(
                mapToRange(value,
                           this->minimum, this->maximum,
                           (float)this->ui->slider->minimum(), (float)this->ui->slider->maximum())
                );
    this->ui->slider->setValue(position);
}

void FloatSlider::setLabel(QLabel* label, float value){
    label->setText(QString::number(value, 'f', 2));
}
