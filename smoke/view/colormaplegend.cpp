#include <math.h>

#include <QDebug>
#include <QPainter>
#include <QString>
#include <QTransform>

#include "colormaplegend.h"
#include "ui_colormaplegend.h"
#include "utilities.h"
#include "settings/settings.h"


const int ColorMapLegend::colorMapImageWidth = 10;
const int ColorMapLegend::tickWidth = 15;
const int ColorMapLegend::maximumNumberOfTicks = 25;
const QPointF ColorMapLegend::textOffset = QPointF(2, 3);

ColorMapLegend::ColorMapLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorMapLegend),
    colorMap(new RainbowColorMap(256)),
    colorBar(0, 0, colorMapImageWidth, 524),
    numberOfTicks(std::min(colorMap->getNumColors(), maximumNumberOfTicks)),
    minimumValue(Settings::defaults::simulation::valueRangeMin),
    maximumValue(Settings::defaults::simulation::valueRangeMax),
    minimumFactor(Settings::defaults::visualization::clampStart),
    maximumFactor(Settings::defaults::visualization::clampEnd)
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
    qDebug() << "void ColorMapLegend::onColorMapChanged: setMinimumValue";
    qDebug() << "void ColorMapLegend::onColorMapChanged: setMaximumValue";
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
    QTransform rotating;
    rotating.rotate(90);
    QImage rotatedImage = colorMap->transformed(rotating);

    painter.drawImage(colorBar, rotatedImage);
}

int ColorMapLegend::getDescriptionLabelHeight()
{
    QFontMetrics fontMetrics(font());
    return fontMetrics.height();
}

void ColorMapLegend::drawTicksAndLabels()
{
    float colorBoxHeight = colorBar.height() / (float) colorMap->getNumColors();
    float colorBoxesPerTick = colorMap->getNumColors() / (float) (numberOfTicks - 1);

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
