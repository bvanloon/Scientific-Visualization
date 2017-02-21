#include "colormaptab.h"
#include "ui_colormaptab.h"
#include "settings/settings.h"

ColorMapTab::ColorMapTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapTab)
{
    ui->setupUi(this);

    setUItoDefaults();
}

ColorMapTab::~ColorMapTab()
{
    delete ui;
}

void ColorMapTab::onValueRangeChanged(float minimum, float maximum)
{
    clampingSlidersSetRange(minimum, maximum);
}

void ColorMapTab::on_clampingMaximumSlider_sliderMoved(int position)
{
    position = std::max(position, this->ui->clampingMinimumSlider->value());
    this->ui->clampingMaximumSlider->setValue(position);
    emit setClampingRange((float) this->ui->clampingMinimumSlider->value(), (float) position);

}

void ColorMapTab::on_clampingMinimumSlider_sliderMoved(int position)
{
    position = std::min(position, this->ui->clampingMaximumSlider->value());
    this->ui->clampingMinimumSlider->setValue(position);
    emit setClampingRange((float) position, (float) this->ui->clampingMaximumSlider->value());
}

void ColorMapTab::on_clampingCheckBox_clicked(bool checked)
{
    clampingUISetDisabled(!checked);
    emit setClamping(checked);
    emit setClampingRange((float) this->ui->clampingMinimumSlider->value(),
                          (float) this->ui->clampingMaximumSlider->value());

}


void ColorMapTab::setUItoDefaults()
{
    this->ui->clampingMinimumSlider->setValue(Settings::defaults::visualization::clampStart);
    this->ui->clampingMaximumSlider->setValue(Settings::defaults::visualization::clampEnd);
    this->ui->clampingCheckBox->setChecked(Settings::defaults::visualization::clampingOn);
    clampingUISetDisabled(!Settings::defaults::visualization::clampingOn);
    clampingSlidersSetRange(Settings::defaults::simulation::valueRangeMin,
                            Settings::defaults::simulation::valueRangeMax);
}

void ColorMapTab::clampingUISetDisabled(bool disabled)
{
    this->ui->clampingMaximumSlider->setDisabled(disabled);
    this->ui->clampingMaximumLabel->setDisabled(disabled);
    this->ui->clampingMinimumSlider->setDisabled(disabled);
    this->ui->clampingMinimumLabel->setDisabled(disabled);
}

void ColorMapTab::clampingSlidersSetRange(float minimum, float maximum)
{
    this->ui->clampingMinimumSlider->setRange(minimum, maximum);
    this->ui->clampingMaximumSlider->setRange(minimum, maximum);
}

