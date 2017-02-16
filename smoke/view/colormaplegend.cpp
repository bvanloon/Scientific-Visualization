#include "colormaplegend.h"
#include "ui_colormaplegend.h"

#include <QDebug>

const int ColorMapLegend::colorMapImageWidth = 10;

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorMap(new RainbowColorMap(255))
{
    ui->setupUi(this);

    draw();
}

ColorMapLegend::~ColorMapLegend()
{
    delete ui;
    delete colorMap;
}

void ColorMapLegend::resizeEvent(QResizeEvent *event)
{
    draw();
}

void ColorMapLegend::draw()
{
    drawColorMapImage();
}

void ColorMapLegend::drawColorMapImage()
{
    QImage scaledImage = colorMap->scaled(colorMapImageWidth, this->height());
    this->ui->colorMapImage->setPixmap(QPixmap::fromImage(scaledImage));
}
