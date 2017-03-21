#include "streamlinestab.h"
#include "ui_streamlinestab.h"

StreamLinesTab::StreamLinesTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamLinesTab)
{
    ui->setupUi(this);
}

StreamLinesTab::~StreamLinesTab()
{
    delete ui;
}

ColorMapTab *StreamLinesTab::getColorMapWidget()
{
   return ui->colorMapWidget;
}
