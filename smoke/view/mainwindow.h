#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <view/canvas.h>
#include "simulation/simulation.h"
#include "colormaplegend.h"
#include "view/simulationsettingpane.h"
#include "view/colormaptab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Canvas *canvas;
    Simulation *simulation;
    ColorMapLegend *colorMapLegend;
    SimulationSettingPane *simulationTab;
    ColorMapTab *colorMapTab;

    void connectCanvasAndSimulation();
    void connectCanvasAndSettings();
    void connectCanvasAndColorMapTab();
    void connectSettingsAndColorMapLegend();
    void connectSettingAndSimulationTab();
    void connectColorMapTabAndColorMapLegend();
};

#endif // MAINWINDOW_H
