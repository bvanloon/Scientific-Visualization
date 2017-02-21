#ifndef VISUALIZATIONSETTINGSPANE_H
#define VISUALIZATIONSETTINGSPANE_H

#include <QWidget>

namespace Ui {
class VisualizationSettingsPane;
}

class VisualizationSettingPane : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizationSettingPane(QWidget *parent = 0);
    ~VisualizationSettingPane();

signals:
    void setClamping(bool clampingOn);

private slots:
    void on_clampingCheckBox_clicked(bool checked);

private:
    Ui::VisualizationSettingsPane *ui;

    void setUItoDefaults();

};

#endif // VISUALIZATIONSETTINGSPANE_H
