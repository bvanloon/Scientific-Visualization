#include "streamsurfacestab.h"
#include "ui_streamsurfacestab.h"

#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

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

ColorMapTab *StreamSurfacesTab::getColorMapWidget()
{
   return ui->colorMapWidget;
}

void StreamSurfacesTab::onEngineToggled(Settings::engines::EnginesTypes engine, bool checked)
{
   if (engine == Settings::engines::EnginesTypes::seedCurves) this->ui->showSeedCurvesCheckBox->setChecked(checked);
}

void StreamSurfacesTab::on_clearSeedCurvesButton_pressed()
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::on_clearSeedCurvesButton_pressed";
}

void StreamSurfacesTab::on_showSeedCurvesCheckBox_clicked(bool checked)
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::on_showSeedCurvesCheckBox_clicked";
//   emit engineToggled(Settings::engines::EnginesTypes::seedCurves, checked);
//   if (checked) emit engineToggled(Settings::engines::EnginesTypes::streamSurfaces, true);
}

void StreamSurfacesTab::setUiToDefaults()
{
   qDebug() << "NOT IMPLEMENTED: StreamSurfacesTab::setUiToDefaults";
}

void StreamSurfacesTab::connectToSettings()
{
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            &Settings::canvas(), SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
}
