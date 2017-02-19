#include "settings.h"
#include "settings/simulations.h"
#include "settings/canvass.h"
#include "settings/visualizations.h"

const Settings::Simulation &Settings::simulation()
{
    return Simulation::instance();
}

const Settings::Canvas &Settings::canvas()
{
    return Canvas::instance();
}

const Settings::Visualization &Settings::visualization()
{
    return Visualization::instance();
}
