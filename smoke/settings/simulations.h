#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include "settingsns.h"

class settingsns::Simulation : public QObject
{
    Q_OBJECT
public:

    static const Simulation &instance();

    int dimension;
    bool frozen;
    float force;

signals:
    void rangeChanged(float minimum, float maximum);

public slots:
    void onDimensionChanged(int newDimension);
    void onForceChanged(float newForce);

private:
    explicit Simulation(QObject *parent = 0);

    Simulation(Simulation const&) = delete;
    void operator=(Simulation const&) = delete;

    void updateGridCellSize();

};

#endif // SIMULATIONS_H
