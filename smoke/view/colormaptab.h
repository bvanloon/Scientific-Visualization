#ifndef COLORMAPTAB_H
#define COLORMAPTAB_H

#include <QWidget>
#include <QColor>
#include <QColorDialog>

#include "colormaps/colormapfactory.h"
#include "settings/visualizationsettings.h"

namespace Ui {
    class ColorMapTab;
}

class ColorMapTab : public QWidget
{
   Q_OBJECT

   public:
      explicit ColorMapTab(QWidget *parent = 0);
      ~ColorMapTab();

      void connectToColorMapSettings(Settings::visualization::ColorMap *colorMap);

      void setColormapSettings(Settings::visualization::ColorMap *value);

signals:
      void setClamping(bool clampingOn);

      void setClampingRange(float minimum, float maximum);

      void colorMapChanged(AbstractColorMap colormap);

      void textureVariableChanged(Settings::sim::Scalar variable);

      void valueRangeChanged(float minimum, float maximum);

   public slots:
      void onValueRangeChanged(Settings::sim::Scalar variable, float min, float max);

   private slots:
      void on_clampingCheckBox_clicked(bool checked);

      void on_clampingMaximumSlider_valueChanged(float value);

      void on_numColorsSlider_valueChanged(int value);

      void on_colormapSelector_currentIndexChanged(int index);

      void on_saturationSlider_valueChanged(float value);

      void on_variableSelector_currentIndexChanged(int index);

      void on_colorPickerButton_clicked();

      void on_clampingMinimumFloatBox_valueChanged(double value);

private:
      Ui::ColorMapTab *ui;
      Settings::visualization::ColorMap* colormapSettings;

      void setUItoDefaults();

      void setUpConnections();

      void clampingUISetDisabled(bool disabled);
};

#endif // COLORMAPTAB_H
