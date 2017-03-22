#ifndef STREAMLINESTAB_H
#define STREAMLINESTAB_H

#include <QWidget>
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

   private:
      Ui::StreamLinesTab *ui;

      void setUiToDefaults();
};

#endif // STREAMLINESTAB_H
