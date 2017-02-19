#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include <QSizeF>
#include "settingsns.h"

class Settings::Simulation : public QObject
{
    Q_OBJECT
public:

    static const Simulation &instance();

    int dimension;
    bool frozen;
    float force;
    QSizeF cellSize;

signals:
    void rangeChanged(float minimum, float maximum);

public slots:
    void onDimensionChanged(int newDimension);
    void onForceChanged(float newForce);
    void onWindowResized(int width, int height);

private:
    explicit Simulation(QObject *parent = 0);

    Simulation(Simulation const&) = delete;
    void operator=(Simulation const&) = delete;

    void updateGridCellSize();
    void updateGridCellSize(int width, int height);

};

#endif // SIMULATIONS_H
