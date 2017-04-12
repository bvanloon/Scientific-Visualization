#include "settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"


const Settings::Simulation& Settings::simulation()
{
   return Simulation::instance();
}

const Settings::Canvas& Settings::canvas()
{
   return Canvas::instance();
}

const Settings::visualization::Smoke& Settings::visualization::smoke()
{
   return Settings::visualization::Smoke::instance();
}

const Settings::visualization::Glyphs& Settings::visualization::glyphs()
{
   return Settings::visualization::Glyphs::instance();
}

QStringList Settings::visualization::getScalarVariableNames()
{
   QStringList names;

   names << "Fluid density"
         << "Fluid velocity magnitude"
         << "Force field magnitude";
   return names;
}

QStringList Settings::visualization::getAllVectorVariableNames()
{
   QStringList names;

   names << "Fluid velocity"
         << "Force"
         << "Fluid density gradient"
         << "Fluid velocity magnitude gradient";

   return names;
}

QStringList Settings::visualization::getNonDerivedVectorVariableNames()
{
   QStringList names;

   names << "Fluid velocity"
         << "Force";

   return names;
}

QStringList Settings::visualization::getGlyphNames()
{
   QStringList names;

   names << "Hedgehogs"
         << "Triangles"
         << "Airplanes"
         << "Cones";

   return names;
}

const Settings::visualization::StreamLines& Settings::visualization::streamLines()
{
   return Settings::visualization::StreamLines::instance();
}

const Settings::visualization::Slices& Settings::visualization::slices()
{
   return Settings::visualization::Slices::instance();
}

const Settings::visualization::StreamSurfaces& Settings::visualization::streamSurfaces()
{
   return Settings::visualization::StreamSurfaces::instance();
}
