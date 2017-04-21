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

      void onVectoFieldChanged(Settings::sim::Vector vectorField, Settings::sim::Scalar magnitude);

   signals:
      void engineToggled(Settings::engines::EnginesTypes engine, bool checked);

      void showStreamSurfaceVerticesToggled(bool toggle);

      void showStreamSurfaceLinesToggled(bool toggle);

      void showStreamSurfaceFaceToggled(bool toggle);

      void vectorFieldChanged(Settings::sim::Vector newVectorField);

      void resolutionChanged(int resolution);

      void numberOfStatesChanged(int newNumberOfStates);

      void divergenceSensitivityChanged(double newSensitivity);

      void clearSeedCurves();

      void toggleAll3Dengines(bool toggle);

      void toggleAllEngines(bool toggle);

      void toggleListenForVertices(bool toggle);

   private slots:
      void on_clearSeedCurvesButton_pressed();

      void on_resolutionSpinBox_valueChanged(int value);

      void on_showLinesCheckBox_clicked(bool checked);

      void on_showVerticesCheckBox_clicked(bool checked);

      void on_numStatesSpinBox_valueChanged(int value);

      void on_showSurfaceCheckBox_clicked(bool checked);

      void on_vectorFieldComboBox_currentIndexChanged(int index);

      void on_divergenceSensitivitySpinBox_valueChanged(double value);

      void on_defineSeedCurveButton_clicked();

   private:
      Ui::StreamSurfacesTab *ui;

      void enterDefineSeedCurveMode();
      void exitDefineSeedCurveMode();

      void fillUI();
      void setUiToDefaults();
      void connectToSettings();
};

#endif // STREAMSURFACESTAB_H
