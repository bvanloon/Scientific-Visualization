#ifndef SIMULATIONSETTINGPANE_H
#define SIMULATIONSETTINGPANE_H

#include <QWidget>
#include "settings/settings.h"

namespace Ui {
    class SimulationSettingPane;
}

class SimulationSettingPane : public QWidget
{
   Q_OBJECT

   public:
      explicit SimulationSettingPane(QWidget *parent = 0);
      ~SimulationSettingPane();

   signals:
      void forceChanged(float force);

      void toggleFrozen();

      void toggleFrozen(bool frozen);

      void step();

      void timeStepChanged(float timeStep);

      void engineToggled(Settings::engines::EnginesTypes engine, bool checked);

   private slots:
      void on_freezeButton_clicked();

      void on_stepButton_clicked();

      void onToggleFrozen(bool frozen);

      void on_timeStepBox_valueChanged(double value);

      void on_glyphsCheckBox_toggled(bool checked);

      void on_smokeCheckBox_toggled(bool checked);

      void on_forceSlider_valueChanged(double value);

   private:
      Ui::SimulationSettingPane *ui;

      void setUItoDefaults();

      void setUpConnections();

      void setFreezeButtonLabel(bool frozen);
};

#endif // SIMULATIONSETTINGPANE_H
