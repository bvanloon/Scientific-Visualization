#ifndef VISUALIZATIONSETTINGSPANE_H
#define VISUALIZATIONSETTINGSPANE_H

#include <QWidget>

namespace Ui {
class VisualizationSettingsPane;
}

class VisualizationSettingsPane : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizationSettingsPane(QWidget *parent = 0);
    ~VisualizationSettingsPane();

signals:
    void setClamping(bool clampingOn);

private:
    Ui::VisualizationSettingsPane *ui;

};

#endif // VISUALIZATIONSETTINGSPANE_H
