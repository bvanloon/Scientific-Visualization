#include <math.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QTransform>

#include "colormaplegend.h"
#include "ui_colormaplegend.h"
#include "utilities.h"
#include "colormaps/colormapfactory.h"
#include "settings/settings.h"


const int ColorMapLegend::colorMapImageWidth = 10;
const int ColorMapLegend::tickWidth = 15;
const int ColorMapLegend::maximumNumberOfTicks = 25;
const QPointF ColorMapLegend::textOffset = QPointF(2, 3);

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorBar(0, 0, colorMapImageWidth, 524),
    minimumValue(Settings::defaults::simulation::valueRangeMin),
    maximumValue(Settings::defaults::simulation::valueRangeMax),
    minimumFactor(Settings::defaults::visualization::colormap::clampMin),
    maximumFactor(Settings::defaults::visualization::colormap::clampMax)
{
    ui->setupUi(this);
    setColorMap(*(ColorMapFactory::get()->createColorMap(
                      Settings::defaults::visualization::colormap::colormap,
                      Settings::defaults::visualization::colormap::numColors)));
}

ColorMapLegend::~ColorMapLegend()
{
    delete ui;
}

void ColorMapLegend::onColorMapChanged(AbstractColorMap colorMap)
{
    setColorMap(colorMap);
    update();
}

void ColorMapLegend::onValueRangeChanged(float minimum, float maximum)
{
    this->minimumValue = minimum;
    this->maximumValue = maximum;
    update();
}

void ColorMapLegend::onClampRangeChanged(float minimum, float maximum)
{
    this->minimumFactor = minimum;
    this->maximumFactor = maximum;
    update();
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
    painter.drawImage(colorBar, colorMapImage);
}

int ColorMapLegend::getDescriptionLabelHeight()
{
    QFontMetrics fontMetrics(font());
    return fontMetrics.height();
}

void ColorMapLegend::drawTicksAndLabels()
{
    float colorBoxHeight = colorBar.height() / numberOfColors;
    float colorBoxesPerTick = numberOfColors / (float) (numberOfTicks - 1);

    float minimumLabel = mapToRange(minimumFactor, 0.0f, 1.0f,
                                    minimumValue, maximumValue);
    float maximumLabel = mapToRange(maximumFactor, 0.0f, 1.0f,
                                    minimumValue, maximumValue);

    float value, y, currentColorBox = 0;
    for(int currentTickNumber = 0; currentTickNumber < (numberOfTicks - 1); currentTickNumber++)
    {
        y = colorBar.top() + colorBoxHeight * round(currentColorBox);

        value = mapToRange(y,
                           (float) colorBar.top(), (float) colorBar.bottom(),
                           minimumLabel, maximumLabel);
        drawTickandLabel(QPointF(0, y), value);

        currentColorBox += colorBoxesPerTick;
    }
    drawTickandLabel(QPointF(0, colorBar.bottom()), maximumLabel);
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
    QString valueStr = QString().setNum(labelValue, 'f', 3);
    painter.drawText(left + textOffset, valueStr);
}

void ColorMapLegend::setColorMap(AbstractColorMap colorMap)
{
    QTransform rotating;
    rotating.rotate(90);
    this->colorMapImage = colorMap.transformed(rotating);
    this->numberOfColors = colorMap.getNumColors();
    this->numberOfTicks = std::min(colorMap.getNumColors(), maximumNumberOfTicks);
}


