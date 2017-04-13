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
   emit clearSeedCurves();
}

void StreamSurfacesTab::on_showSeedCurvesCheckBox_clicked(bool checked)
{
   emit engineToggled(Settings::engines::EnginesTypes::seedCurves, checked);
   if (checked) emit engineToggled(Settings::engines::EnginesTypes::streamSurfaces, true);
}

void StreamSurfacesTab::setUiToDefaults()
{
   this->ui->showSeedCurvesCheckBox->setChecked(Settings::defaults::engines::activeEngines[Settings::engines::EnginesTypes::seedCurves]);
   this->ui->showLinesCheckBox->setChecked(Settings::visualization::streamSurfaces().showLines);
   this->ui->showVerticesCheckBox->setChecked(Settings::visualization::streamSurfaces().showVertices);
}

void StreamSurfacesTab::connectToSettings()
{
   connect(this, SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            &Settings::canvas(), SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
   connect(&Settings::canvas(), SIGNAL(engineToggled(Settings::engines::EnginesTypes,bool)),
            this, SLOT(onEngineToggled(Settings::engines::EnginesTypes,bool)));
   connect(this, SIGNAL(clearSeedCurves()),
           &Settings::visualization::streamSurfaces(), SLOT(onClearSeedCurves()));
   connect(this, SIGNAL(resolutionChanged(int)),
           &Settings::visualization::streamSurfaces(), SLOT(onResolutionChanged(int)));
   connect(this, SIGNAL(showStreamSurfaceLinesToggled(bool)),
           &Settings::visualization::streamSurfaces(), SLOT(onShowStreamSurfaceLinesToggled(bool)));
   connect(this, SIGNAL(showStreamSurfaceVerticesToggled(bool)),
           &Settings::visualization::streamSurfaces(), SLOT(onShowStreamSurfaceVerticesToggled(bool)));
}

void StreamSurfacesTab::on_resolutionSpinBox_valueChanged(int value)
{
   emit resolutionChanged(value);
}

void StreamSurfacesTab::on_showLinesCheckBox_clicked(bool checked)
{
   emit showStreamSurfaceLinesToggled(checked);
}

void StreamSurfacesTab::on_showVerticesCheckBox_clicked(bool checked)
{
   emit showStreamSurfaceVerticesToggled(checked);
}
