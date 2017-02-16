#include <math.h>

#include <QDebug>
#include <QPainter>
#include <QString>

#include "colormaplegend.h"
#include "ui_colormaplegend.h"
#include "utilities.h"


const int ColorMapLegend::colorMapImageWidth = 10;
const int ColorMapLegend::tickWidth = 15;
const int ColorMapLegend::maximumNumberOfTicks = 30;

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorMap(new RainbowColorMap(256)),
    colorBar(0, 0, colorMapImageWidth, 524),
    numberOfTicks(std::min(colorMap->getNumColors(), maximumNumberOfTicks)),
    minimumValue(0),
    maximumValue(20),
    textOffset(2, 3)
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
    colorBar.setTop(getDescriptionLabelHeight());
    colorBar.setHeight(event->size().height() - 2 * getDescriptionLabelHeight());
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

int ColorMapLegend::getDescriptionLabelHeight()
{
    QFontMetrics fontMetrics(font());
    return fontMetrics.height();
}

void ColorMapLegend::drawTicksAndLabels()
{
    float colorBoxHeight = colorBar.height() / (float) colorMap->getNumColors();
    int numberOfColorBoxesPerTick = round(colorMap->getNumColors() / (numberOfTicks - 1));

    float value;
    float y = colorBar.top();
    for(int tickNumber = 0;
        tickNumber < numberOfTicks;
        tickNumber++, y+= colorBoxHeight * numberOfColorBoxesPerTick)
    {
        value = mapToRange(y, (float) colorBar.top(), (float) colorBar.bottom(), minimumValue, maximumValue);
        drawTickandLabel(QPointF(0, y), value);
    }
    drawTickandLabel(QPointF(0, colorBar.bottom()), maximumValue);
}

void ColorMapLegend::drawTickandLabel(QPointF left, float value)
{
    QPainter painter(this);
    QPointF right = left + QPointF(tickWidth, 0);
    painter.drawLine(left, right);

    drawLabel(right, value);
}

void ColorMapLegend::drawLabel(QPointF left, float labelValue)
{
    QPainter painter(this);
    QString valueStr = QString().setNum(labelValue, 'g', 2);
    painter.drawText(left + textOffset, valueStr);
}
