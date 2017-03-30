#ifndef SLICESTAB_H
#define SLICESTAB_H

#include <QWidget>

namespace Ui {
class SlicesTab;
}

class SlicesTab : public QWidget
{
    Q_OBJECT

public:
    explicit SlicesTab(QWidget *parent = 0);
    ~SlicesTab();

private:
    Ui::SlicesTab *ui;

    void connectToSettings();
    void setUItoDefaults();
};

#endif // SLICESTAB_H
