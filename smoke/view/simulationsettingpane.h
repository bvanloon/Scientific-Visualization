#ifndef SIMULATIONSETTINGPANE_H
#define SIMULATIONSETTINGPANE_H

#include <QWidget>

namespace Ui {
class SimulationSettingPane;
}

class SimulationSettingPane : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationSettingPane(QWidget *parent = 0);
    ~SimulationSettingPane();

private:
    Ui::SimulationSettingPane *ui;
};

#endif // SIMULATIONSETTINGPANE_H
