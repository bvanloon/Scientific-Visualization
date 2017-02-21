#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <view/canvas.h>
#include "simulation/simulation.h"
#include "colormaplegend.h"
#include "view/simulationsettingpane.h"
#include "view/visualizationsettingpane.h"

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
    SimulationSettingPane *simulationSettingPane;
    VisualizationSettingPane *visualiationSettingsPane;

    void connectCanvasAndSimulation();
    void connectSettingsAndCanvas();
    void connectSettingsAndColorMapLegend();
    void connectSettingAndSimulationSettingPane();
    void connectCanvasAndVisualizationSettingsPane();
};

#endif // MAINWINDOW_H
