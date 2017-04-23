#ifndef GLYPHSTAB_H
#define GLYPHSTAB_H

#include <QWidget>

#include "view/colormaptab.h"

namespace Ui {
    class GlyphsTab;
}

class GlyphsTab : public QWidget
{
   Q_OBJECT

   public:
      explicit GlyphsTab(QWidget *parent = 0);
      ~GlyphsTab();

      ColorMapTab *getColorMapWidget();

   signals:
      void gridDimensionChanged(int widht, int height);
      void gridDimensionChanged(QSizeF newDimension);

      void vectorFieldChanged(Settings::sim::Vector vectorField);

      void glyphChanged(Settings::sim::GlyphsType glyph);

      void jitterFactorChanged(double value);

      void scaleChanged(double scale);

   private slots:
      void on_gridHeightSpinBox_valueChanged(int height);

      void on_gridWidthSpinBox_valueChanged(int width);

      void on_vectorFieldComboBox_currentIndexChanged(int index);

      void on_glyphSelector_currentIndexChanged(int index);

      void on_scale_valueChanged(double scale);

      void on_jitterFactorSpinBox_valueChanged(double arg1);

   private:
      Ui::GlyphsTab *ui;

      void setUiToDefaults();

      void connectToSettings();

      void updateScaleSpinBoxConfiguration(double currentValue);
};

#endif // GLYPHSTAB_H
