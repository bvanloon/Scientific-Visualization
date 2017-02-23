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

public slots:
    void onValueRangeChanged(float minimum, float maximum);

private slots:
    void on_clampingCheckBox_clicked(bool checked);

private:
    Ui::ColorMapTab *ui;

    void setUItoDefaults();

    void clampingUISetDisabled(bool disabled);
};

#endif // COLORMAPTAB_H
