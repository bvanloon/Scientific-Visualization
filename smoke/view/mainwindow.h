#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <view/canvas.h>
#include "simulation/simulation.h"
#include "colormaplegend.h"
#include "view/simulationtab.h"
#include "view/colormaptab.h"
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

    KeyboardHandler* keyboardHandler;

public slots:
    void onOpenGLReady();

private:
    Ui::MainWindow *ui;

    Canvas *canvas;
    Simulation *simulation;
    SimulationSettingPane *simulationTab;
    ColorMapTab *smokeColorMapTab;

    void setUpConnections();

    void connectCanvasAndThis();
    void connectCanvasAndSimulation();
    void connectCanvasAndSettings();
    void connectCanvasAndColorMapTab();

    void connectColorMapTabAndEngine();

    void connectSimulationTabAndSettings();
    void connectSimulationTabAndSimulation();

    void connectSmokeColorMapTabAndSettings();

    void connectKeyBoardHandlerAndSimulation();
};

#endif // MAINWINDOW_H
