#ifndef STREAMSURFACESTAB_H
#define STREAMSURFACESTAB_H

#include <QWidget>

namespace Ui {
    class StreamSurfacesTab;
}

class StreamSurfacesTab : public QWidget
{
   Q_OBJECT

   public:
      explicit StreamSurfacesTab(QWidget *parent = 0);
      ~StreamSurfacesTab();

   private slots:
      void on_clearSeedCurvesButton_pressed();

      void on_showSeedCurvesCheckBox_clicked(bool checked);

   private:
      Ui::StreamSurfacesTab *ui;

      void setUiToDefaults();
      void connectToSettings();
};

#endif // STREAMSURFACESTAB_H
