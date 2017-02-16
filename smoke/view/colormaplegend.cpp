#include <math.h>

#include "colormaplegend.h"
#include "ui_colormaplegend.h"

#include <QDebug>
#include <QPainter>


const int ColorMapLegend::colorMapImageWidth = 10;
const int ColorMapLegend::tickWidth = 15;
const int ColorMapLegend::maximumNumberOfTicks = 5;

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorMap(new RainbowColorMap(26)),
    colorBar(0, 0, colorMapImageWidth, 524),
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
    drawTicks();
}

void ColorMapLegend::drawColorMapImage()
{
    QPainter painter(this);
    painter.drawImage(colorBar, *colorMap);
}

void ColorMapLegend::drawLabels()
{
    //Probbaly some calls to drawLabel and drawLabelText
}

void ColorMapLegend::drawLabel()
{

}

void ColorMapLegend::drawTicks()
{
    float colorBoxHeight = colorBar.height() / (float) colorMap->getNumColors();
    int numberOfColorBoxesPerTick = round(colorMap->getNumColors() / (numberOfTicks - 1));
    for(float y = 0;
        y < colorBar.height();
        y+= colorBoxHeight * numberOfColorBoxesPerTick){
        drawTick(QPointF(0, y));
    }
    drawTick(QPointF(0, colorBar.height() - 1));
}

void ColorMapLegend::drawTick(QPointF left)
{
    QPainter painter(this);
    QPointF right = left + QPointF(tickWidth, 0);
    painter.drawLine(left, right);
}
