#ifndef VISUALIZATIONS_H
#define VISUALIZATIONS_H

#include <QObject>
#include "settings.h"
#include "simulation/simulation.h"

class Settings::Visualization : public QObject
{
    Q_OBJECT
public:

    enum ScalarVariable {
        fluidDensity,
        fluidVelocity,
        forceFieldMagnitude
    };

    static const Visualization &instance();

    static QStringList getScalarVariableNames();

    ::Simulation::textureCoordinateGetter textureGetter;
    float vectorScale;

signals:

public slots:
    void onScalarVariableChanged(Settings::Visualization::ScalarVariable scalarVariable);

private:
    explicit Visualization(QObject *parent = 0);

    Visualization(Visualization const&) = delete;
    void operator=(Visualization const&) = delete;

    void setTextureGetter(Settings::Visualization::ScalarVariable scalar);
};

#endif // VISUALIZATIONS_H
