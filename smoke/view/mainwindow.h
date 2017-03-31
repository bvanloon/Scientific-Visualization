#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <view/canvas.h>
#include "view/simulationtab.h"
#include "view/colormaptab.h"
#include "view/glyphstab.h"
#include "view/streamlinestab.h"

#include "simulation/simulation.h"
#include "simulation/simulationstatehistory.h"
#include "colormaplegend.h"

#include "keyboardhandler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

   public:
      explicit MainWindow(QWidget *parent = 0);
      ~MainWindow();

      KeyboardHandler *keyboardHandler;

   signals:
      void finishedSettingUpConnections();

   public slots:
      void onOpenGLReady();

   private:
      Ui::MainWindow *ui;

      Canvas *canvas;
      Simulation *simulation;

      SimulationSettingPane *simulationTab;
      ColorMapTab *smokeTab;
      GlyphsTab *glyphsTab;
      StreamLinesTab *streamLinesTab;

      void setUpConnections();

      void connectSimuationStateHistory();

      //Canvas
      void connectCanvasAndThis();

      void connectCanvasAndSimulation();

      void connectCanvasAndSettings();

      void connectCanvasAndTabs();

      //Connect to objects that want to receive the finishedConnections signal
      void connectThisToFinishConnectionsReceivers();


      //Engines
      void connectGlyphEngineAndGlyphTab();

      void connectGlyphEngineAndSettings();

      void connectGlyphSlicesEngineAndGlyphTab();

      void connectGlyphSlicesEngineAndSettings();

      void connectAbstractEngine(Settings::engines::EnginesTypes engine,
                                 ColorMapTab *colormapTab,
                                 Settings::visualization::ColorMap *colorMapSetings);

      void connectAbstractSliceEngine(Settings::engines::EnginesTypes engineType,
                                      ColorMapTab *colormapTab,
                                      Settings::visualization::ColorMap *colorMapSetings);

      //Tabs
      void connectSimulationTabAndSettings();

      void connectSimulationTabAndSimulation();

      void connectGlyphTabAndSettings();

      void connectStreamLinesTabAndSettings();

      void connectTabs();


      //Other IO
      void connectKeyBoardHandlerAndSimulation();
};

#endif // MAINWINDOW_H
