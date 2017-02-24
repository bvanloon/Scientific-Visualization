#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settings.h"

class Settings::Visualization : public QObject
{
    Q_OBJECT
public:

    enum scalarVarible {
        fluidDensity,
        fluidVelocity,
        forceFieldMagnitude
    };

    static const Visualization &instance();

    float vectorScale;

signals:

public slots:

private:
    explicit Visualization(QObject *parent = 0);

    Visualization(Visualization const&) = delete;
    void operator=(Visualization const&) = delete;
};

#endif // VISUALIZATIONS_H
