#include "simulationsettings.h"
#include "settings/canvassettings.h"
#include "fftw.h"
#include <QDebug>

Settings::Simulation::Simulation(QObject *parent) :
   QObject(parent),
   dimension(50),
   frozen(false),
   force(10.0f),
   timestep(0.4),
   cellSize(-1, -1)
{
}


const Settings::Simulation& Settings::Simulation::instance()
{
   static Simulation instance;

   return instance;
}


void Settings::Simulation::onDimensionChanged(int newDimension)
{
   this->dimension = newDimension;
   updateGridCellSize();
}


void Settings::Simulation::onForceChanged(float newForce)
{
   this->force = newForce;
   emit forceChanged(newForce);
}


void Settings::Simulation::onWindowResized(int width, int height)
{
   updateGridCellSize(width, height);
   qDebug() << "Settings::Simulation::onWindowResized: Notify the visualization grid of the changed cell size";
}


void Settings::Simulation::onToggleFrozen()
{
   this->frozen = !this->frozen;
}


void Settings::Simulation::onToggleFrozenKeyboard()
{
   this->frozen = !this->frozen;
   emit toggleFrozen(this->frozen);
}


void Settings::Simulation::onTimeStepChanged(float value)
{
   this->timestep = value;
}


void Settings::Simulation::updateGridCellSize()
{
   updateGridCellSize(Settings::canvas().size.width(), Settings::canvas().size.height());
}


void Settings::Simulation::updateGridCellSize(int width, int height)
{
   cellSize.setHeight((fftw_real)height / (fftw_real)(dimension + 1));
   cellSize.setWidth((fftw_real)width / (fftw_real)(dimension + 1));
}
