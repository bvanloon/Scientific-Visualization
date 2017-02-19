#include "settingsns.h"
#include "settings/simulations.h"

const settingsns::Simulation &settingsns::simulation()
{
    return Simulation::instance();
}
