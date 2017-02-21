#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <view/canvas.h>
#include "simulation/simulation.h"
#include "colormaplegend.h"
#include "view/simulationsettingpane.h"
#include "view/colormapsettingpane.h"

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
    ColorMapSettingPane *visualiationSettingsPane;

    void connectCanvasAndSimulation();
    void connectSettingsAndCanvas();
    void connectSettingsAndColorMapLegend();
    void connectSettingAndSimulationSettingPane();
    void connectCanvasAndColorMapSettingsPane();
    void connectColorMapSettingsPaneAndColorMapLegend();
};

#endif // MAINWINDOW_H
