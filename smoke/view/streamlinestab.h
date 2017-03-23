#ifndef STREAMLINESTAB_H
#define STREAMLINESTAB_H

#include <QWidget>
#include <QDoubleSpinBox>
#include "settings/settings.h"
#include "view/colormaptab.h"

namespace Ui {
    class StreamLinesTab;
}

class StreamLinesTab : public QWidget
{
   Q_OBJECT

   public:
      explicit StreamLinesTab(QWidget *parent = 0);
      ~StreamLinesTab();

      ColorMapTab *getColorMapWidget();

   public slots:
      void onEngineToggled(Settings::engines::EnginesTypes engine, bool checked);

   signals:
      void timeStepChanged(double newTimeStep);

      void maximumTimeChanged(double newMaximumTime);

      void edgeLengthFactorChanged(double newEdgeLengthFactor);

      void maximumTotalLengthFactorChanged(double newValue);

      void clearSeedPoints();

      void engineToggled(Settings::engines::EnginesTypes engine, bool checked);

   private slots:

      void on_timeStepSelector_valueChanged(double arg1);

      void on_clearSeedPointsButton_clicked();

      void on_showSeedPoinsCheckBox_clicked(bool checked);

      void on_maximumTimeSelector_valueChanged(double value);

      void on_edgeLengthSelector_valueChanged(double value);

      void on_maximumLengthSelector_valueChanged(double value);

   private:
      Ui::StreamLinesTab *ui;

      void setUiToDefaults();

      void setSpinBoxWithSpecialValueToDefault(QDoubleSpinBox *spinBox, double value);
};

#endif // STREAMLINESTAB_H
