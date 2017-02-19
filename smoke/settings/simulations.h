#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include "settingsns.h"

class settingsns::Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);

signals:

public slots:
};

#endif // SIMULATIONS_H
