#include "simulations.h"


const settingsns::Simulation &settingsns::Simulation::instance()
{
    static Simulation instance;
    return instance;
}

settingsns::Simulation::Simulation(QObject *parent):
    QObject(parent)
{

}
