#include "settingsns.h"
#include "settings/simulations.h"
#include "settings/canvass.h"
#include "settings/visualizations.h"

const settingsns::Simulation &settingsns::simulation()
{
    return Simulation::instance();
}

const settingsns::Canvas &settingsns::canvas()
{
    return Canvas::instance();
}

const settingsns::Visualization &settingsns::visualization()
{
    return Visualization::instance();
}
