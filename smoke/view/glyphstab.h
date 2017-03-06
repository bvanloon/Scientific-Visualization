#ifndef GLYPHSTAB_H
#define GLYPHSTAB_H

#include <QWidget>

#include "view/colormaptab.h"

namespace Ui {
class GlyphsTab;
}

class GlyphsTab : public QWidget
{
    Q_OBJECT

public:
    explicit GlyphsTab(QWidget *parent = 0);
    ~GlyphsTab();

    ColorMapTab* getColorMapWidget();

private:
    Ui::GlyphsTab *ui;

    void setUiToDefaults();
    void setUpConnections();
};

#endif // GLYPHSTAB_H
