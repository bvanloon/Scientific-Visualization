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

   private slots:
      void on_gridHeightSpinBox_valueChanged(int height);

      void on_gridWidthSpinBox_valueChanged(int width);

      void on_vectorFieldComboBox_currentIndexChanged(int index);

      void on_scalarFieldComboBox_currentIndexChanged(int index);

   private:
      Ui::GlyphsTab *ui;

      void setUiToDefaults();

      void setUpConnections();
};

#endif // GLYPHSTAB_H
