#include "slicestab.h"
#include "ui_slicestab.h"

SlicesTab::SlicesTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlicesTab)
{
    ui->setupUi(this);
}

SlicesTab::~SlicesTab()
{
    delete ui;
}
