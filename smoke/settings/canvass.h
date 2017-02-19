#ifndef CANVASS_H
#define CANVASS_H

#include <QObject>
#include <QSize>

#include "settings/settingsns.h"

class settingsns::Canvas : public QObject
{
    Q_OBJECT
public:

    static const Canvas &instance();

    QSize size;

signals:

public slots:

private:
    explicit Canvas(QObject *parent = 0);

    Canvas(Canvas const&) = delete;
    void operator=(Canvas const&) = delete;
};

#endif // CANVASS_H
