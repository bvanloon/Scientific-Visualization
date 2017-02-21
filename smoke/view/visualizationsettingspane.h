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

private slots:
    void on_clampingCheckBox_clicked(bool checked);

private:
    Ui::VisualizationSettingsPane *ui;

    void setUItoDefaults();

};

#endif // VISUALIZATIONSETTINGSPANE_H
