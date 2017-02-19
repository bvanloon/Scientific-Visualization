#include "settingsns.h"
#include "settings/simulations.h"
#include "settings/canvass.h"

const settingsns::Simulation &settingsns::simulation()
{
    return Simulation::instance();
}

const settingsns::Canvas &settingsns::canvas()
{
    return Canvas::instance();
}
