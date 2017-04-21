#ifndef SIMULATIONSETTINGPANE_H
#define SIMULATIONSETTINGPANE_H

#include <QWidget>
#include "settings/settings.h"
#include <QCheckBox>
#include <QMap>
#include "utilities/rotation.h"

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

      void rotationChanged(Rotation::axis axis, int newAngle);

      void scalingFactorChanged(double newScalingFactor);

      void setViewMatrixToTopDownView();

      void setViewMatrixToSideView();

      void resetView();

   public slots:
      void onEngineToggled(Settings::engines::EnginesTypes engine, bool checked);

      void onScalingFactorChanged(double scalingFactor);

      void onRotationChanged(Rotation rotation);

      void onAllConnectionsAreSetUp();

   private slots:
      void on_freezeButton_clicked();

      void on_stepButton_clicked();

      void onToggleFrozen(bool frozen);

      void on_timeStepBox_valueChanged(double value);

      void on_glyphsCheckBox_toggled(bool checked);

      void on_smokeCheckBox_toggled(bool checked);

      void on_forceSlider_valueChanged(double value);

      void on_streamLinesCheckBox_clicked(bool checked);

      void on_glyphSlicesCheckBox_clicked(bool checked);

      void on_smokeSlicesCheckBox_clicked(bool checked);

      void on_streamLineSlicesCheckBox_clicked(bool checked);

      void on_streamSurfacesCheckBox_clicked(bool checked);

      void on_xRotationDial_valueChanged(int value);

      void on_yRotationDial_valueChanged(int value);

      void on_zRotationDial_valueChanged(int value);

      void on_scaleFactorSpinBox_valueChanged(double arg1);

      void on_resetViewButton_clicked();

      void on_sideViewButton_pressed();

      void on_topDownViewButton_pressed();

   private:
      typedef QMap<Settings::engines::EnginesTypes, QCheckBox *> EngineMap;

      Ui::SimulationSettingPane *ui;

      void setUItoDefaults();

      void setEnginesToDefaults();

      void setUpPrivateConnections();

      void connectToSettings();

      void registerEngines();

      void setFreezeButtonLabel(bool frozen);

      void toggle3DEngines(bool toggle);

      void toggle2DEngines(bool toggle);

      bool is3DEngine(Settings::engines::EnginesTypes engine);

      bool is2DEngine(Settings::engines::EnginesTypes engine);

      void register2DEngine(Settings::engines::EnginesTypes engine, QCheckBox *engineCheckBox = nullptr);
      void register3DEngines(Settings::engines::EnginesTypes engine, QCheckBox *engineCheckBox);

      EngineMap engines;
      EngineMap engines2D;
      EngineMap engines3D;
};

#endif // SIMULATIONSETTINGPANE_H
