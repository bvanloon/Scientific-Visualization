#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <view/canvas.h>
#include "simulation/simulation.h"
#include "settings/settings.h"
#include "colormaplegend.h"

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
    Settings *settings;
    ColorMapLegend *colorMapLegend;

    void connectCanvasAndSimulation();
    void connectSettingsAndCanvas();
    void connectSimulationAndColorMapLegend();
};

#endif // MAINWINDOW_H
