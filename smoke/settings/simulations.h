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

signals:

public slots:
    void onDimensionChanged(int newDimension);

private:
    explicit Simulation(QObject *parent = 0);

    Simulation(Simulation const&) = delete;
    void operator=(Simulation const&) = delete;

    void updateGridCellSize();

};

#endif // SIMULATIONS_H
