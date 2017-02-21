#ifndef COLORMAPTAB_H
#define COLORMAPTAB_H

#include <QWidget>

namespace Ui {
class ColorMapTab;
}

class ColorMapTab : public QWidget
{
    Q_OBJECT

public:
    explicit ColorMapTab(QWidget *parent = 0);
    ~ColorMapTab();

signals:
    void setClamping(bool clampingOn);
    void setClampingRange(float minimum, float maximum);

public slots:
    void onValueRangeChanged(float minimum, float maximum);

private slots:
    void on_clampingMaximumSlider_sliderMoved(int position);
    void on_clampingMinimumSlider_sliderMoved(int position);
    void on_clampingCheckBox_clicked(bool checked);

private:
    Ui::ColorMapTab *ui;

    void setUItoDefaults();

    void clampingUISetDisabled(bool disabled);
    void clampingSlidersSetRange(float minimum, float maximum);
};

#endif // COLORMAPTAB_H
