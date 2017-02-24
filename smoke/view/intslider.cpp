#include "intslider.h"
#include "ui_intslider.h"

IntSlider::IntSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntSlider)
{
    ui->setupUi(this);
}

IntSlider::~IntSlider()
{
    delete ui;
}

void IntSlider::init(int minimum, int maximum, int value)
{
    setMinimum(minimum);
    setMaximum(maximum);
    setValue(value);
}

void IntSlider::setMinimum(int minimum)
{
    setLabel(ui->minimumLabel, minimum);
    ui->slider->setMinimum(minimum);
}

void IntSlider::setMaximum(int maximum)
{
    setLabel(ui->maximumLabel, maximum);
    ui->slider->setMaximum(maximum);
}

void IntSlider::setValue(int value)
{
    setLabel(ui->valueLabel, value);
    ui->slider->setValue(value);
}

void IntSlider::setLabel(QLabel *label, int value)
{
    label->setText(QString::number(value, 'f', 0));
}
