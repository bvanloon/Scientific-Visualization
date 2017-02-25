#include "settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

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
