#include "floatslider.h"
#include "ui_floatslider.h"

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

void FloatSlider::init(int numSteps, float minimum, float maximum)
{
    this->numSteps = numSteps;
    this->minimum = minimum;
    this->maximum = maximum;
}
