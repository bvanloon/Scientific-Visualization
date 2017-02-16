#include <math.h>

#include "colormaplegend.h"
#include "ui_colormaplegend.h"

#include <QDebug>
#include <QPainter>


const int ColorMapLegend::colorMapImageWidth = 10;
const int ColorMapLegend::tickWidth = 15;
const int ColorMapLegend::maximumNumberOfTicks = 20;

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorMap(new RainbowColorMap(40)),
    colorBar(0, 0, colorMapImageWidth, 524),
    minimumValue(0),
    maximumValue(39),
    numberOfTicks(std::min(colorMap->getNumColors(), maximumNumberOfTicks))
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
    drawLabels();
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
        tickNumber < (numberOfTicks - 1);
        tickNumber++, y+= colorBoxHeight * numberOfColorBoxesPerTick){
        drawTick(QPointF(0, y));
        drawLabel()
    }
    drawTick(QPointF(0, colorBar.height() - 1));
}

void ColorMapLegend::drawTick(QPointF left)
{
    QPainter painter(this);
    QPointF right = left + QPointF(tickWidth, 0);
    painter.drawLine(left, right);
}

void ColorMapLegend::drawLabel(QPointF left, float labelValue)
{

}
