#include "streamsurfacestab.h"
#include "ui_streamsurfacestab.h"

StreamSurfacesTab::StreamSurfacesTab(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::StreamSurfacesTab)
{
   ui->setupUi(this);
}

StreamSurfacesTab::~StreamSurfacesTab()
{
   delete ui;
}
