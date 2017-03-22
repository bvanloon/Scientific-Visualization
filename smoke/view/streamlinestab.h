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

    signals:
      void timeStepChanged(double newTimeStep);
      void edgeLengthFactorChanged(double newFactor);
      void clearSeedPoints();

    private slots:

      void on_timeStepSelector_valueChanged(double arg1);

      void on_lengthFactorSelector_valueChanged(double arg1);

      void on_clearSeedPointsButton_clicked();

private:
        Ui::StreamLinesTab *ui;

        void setUiToDefaults();
};

#endif // STREAMLINESTAB_H
