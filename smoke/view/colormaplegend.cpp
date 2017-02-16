#include <math.h>

#include "colormaplegend.h"
#include "ui_colormaplegend.h"

#include <QDebug>
#include <QPainter>


const int ColorMapLegend::colorMapImageWidth = 10;
const int ColorMapLegend::tickWidth = 15;
const int ColorMapLegend::maximumNumberOfTicks = 21;

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorMap(new RainbowColorMap(20)),
    colorBar(0, 0, colorMapImageWidth, 524),
    numberOfTicks(std::min(colorMap->getNumColors(), maximumNumberOfTicks)),
    minimumValue(0),
    maximumValue(19)
{
    ui->setupUi(this);
}

ColorMapLegend::~ColorMapLegend()
{
    delete ui;
    delete colorMap;
}

void ColorMapLegend::onColorMapChanged(AbstractColorMap colorMap)
{
    numberOfTicks = std::min(colorMap.getNumColors(), maximumNumberOfTicks);
}

void ColorMapLegend::resizeEvent(QResizeEvent *event)
{
    colorBar.setHeight(event->size().height());
}

void ColorMapLegend::paintEvent(QPaintEvent *event)
{
    drawColorMapImage();
    drawTicksAndLabels();
}

void ColorMapLegend::drawColorMapImage()
{
    QPainter painter(this);
    painter.drawImage(colorBar, *colorMap);
}

void ColorMapLegend::drawTicksAndLabels()
{
    float colorBoxHeight = colorBar.height() / (float) colorMap->getNumColors();
    int numberOfColorBoxesPerTick = round(colorMap->getNumColors() / (numberOfTicks - 1));
    float y = 0;
    for(int tickNumber = 0;
        tickNumber < numberOfTicks;
        tickNumber++, y+= colorBoxHeight * numberOfColorBoxesPerTick){
        drawTickandLabel(QPointF(0, y));
    }
    drawTickandLabel(QPointF(0, colorBar.height() - 1));
}

void ColorMapLegend::drawTickandLabel(QPointF left)
{
    QPainter painter(this);
    QPointF right = left + QPointF(tickWidth, 0);
    painter.drawLine(left, right);

    drawLabel(right, 0.0);
}

void ColorMapLegend::drawLabel(QPointF left, float labelValue)
{

}
