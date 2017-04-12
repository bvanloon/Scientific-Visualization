#include "streamsurfacestab.h"
#include "ui_streamsurfacestab.h"

StreamSurfacesTab::StreamSurfacesTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::StreamSurfacesTab)
{
   ui->setupUi(this);
   connectToSettings();
   setUiToDefaults();
}

StreamSurfacesTab::~StreamSurfacesTab()
{
   delete ui;
}

void StreamSurfacesTab::on_clearSeedCurvesButton_pressed()
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::on_clearSeedCurvesButton_pressed";
}

void StreamSurfacesTab::on_showSeedCurvesCheckBox_clicked(bool checked)
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::on_showSeedCurvesCheckBox_clicked";
}

void StreamSurfacesTab::setUiToDefaults()
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::setUiToDefaults";
}

void StreamSurfacesTab::connectToSettings()
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::connectToSettings";
}
