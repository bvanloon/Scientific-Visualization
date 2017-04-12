#ifndef STREAMSURFACESTAB_H
#define STREAMSURFACESTAB_H

#include <QWidget>
#include "settings/settings.h"
#include "view/colormaptab.h"

namespace Ui {
    class StreamSurfacesTab;
}

class StreamSurfacesTab : public QWidget
{
   Q_OBJECT

   public:
      explicit StreamSurfacesTab(QWidget *parent = 0);
      ~StreamSurfacesTab();

      ColorMapTab *getColorMapWidget();

   public slots:
      void onEngineToggled(Settings::engines::EnginesTypes engine, bool checked);

   signals:
      void engineToggled(Settings::engines::EnginesTypes engine, bool checked);

   private slots:
      void on_clearSeedCurvesButton_pressed();

      void on_showSeedCurvesCheckBox_clicked(bool checked);

   private:
      Ui::StreamSurfacesTab *ui;

      void setUiToDefaults();
      void connectToSettings();
};

#endif // STREAMSURFACESTAB_H
