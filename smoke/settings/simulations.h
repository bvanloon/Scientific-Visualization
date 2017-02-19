#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include "settingsns.h"

class settingsns::Simulation : public QObject
{
    Q_OBJECT
public:

    static const Simulation &instance();

signals:

public slots:

private:
    explicit Simulation(QObject *parent = 0);

    Simulation(Simulation const&) = delete;
    void operator=(Simulation const&) = delete;
};

#endif // SIMULATIONS_H
