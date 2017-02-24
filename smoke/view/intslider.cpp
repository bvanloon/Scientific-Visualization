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

}
