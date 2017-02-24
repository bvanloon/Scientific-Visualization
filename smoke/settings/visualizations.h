#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settings.h"
#include "simulation/simulation.h"

class Settings::Visualization : public QObject
{
    Q_OBJECT
public:

    enum ScalarVarible {
        fluidDensity,
        fluidVelocity,
        forceFieldMagnitude
    };

    static const Visualization &instance();

    ::Simulation::textureCoordinateGetter textureGetter;
    float vectorScale;

signals:

public slots:

private:
    explicit Visualization(QObject *parent = 0);

    Visualization(Visualization const&) = delete;
    void operator=(Visualization const&) = delete;
};

#endif // VISUALIZATIONS_H
