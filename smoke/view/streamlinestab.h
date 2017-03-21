#ifndef STREAMLINESTAB_H
#define STREAMLINESTAB_H

#include <QWidget>

namespace Ui {
class StreamLinesTab;
}

class StreamLinesTab : public QWidget
{
    Q_OBJECT

public:
    explicit StreamLinesTab(QWidget *parent = 0);
    ~StreamLinesTab();

private:
    Ui::StreamLinesTab *ui;
};

#endif // STREAMLINESTAB_H
