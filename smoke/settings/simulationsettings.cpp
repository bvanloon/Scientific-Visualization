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
   scalarRanges.insert(Settings::visualization::ScalarVariable::fluidDensity, QPair<float, float>(0.0f, force));
   scalarRanges.insert(Settings::visualization::ScalarVariable::fluidVelocityMagnitude, QPair<float, float>(0.0f, 0.1f));
   scalarRanges.insert(Settings::visualization::ScalarVariable::forceFieldMagnitude, QPair<float, float>(0.0f, 0.5f));
}

void Settings::Simulation::updateRange(Settings::visualization::ScalarVariable scalar, float minimum, float maximum)
{
   QPair<float, float> range = scalarRanges.find(scalar).value();
   range.first = minimum;
   range.second = maximum;
   qDebug() << "Settings::Simulation::updateRange: emit valueRangeChanged(scalar, minimum, maximum)";
}

const Settings::Simulation& Settings::Simulation::instance()
{
   static Simulation instance;

   return instance;
}

QPair<float, float> Settings::Simulation::getRange(Settings::visualization::ScalarVariable scalar) const
{
   return this->scalarRanges.constFind(scalar).value();
}

void Settings::Simulation::onDimensionChanged(int newDimension)
{
   this->dimension = newDimension;
   updateGridCellSize();
}

void Settings::Simulation::onForceChanged(float newForce)
{
   this->force = newForce;
   updateRange(Settings::visualization::fluidDensity, 0.0f, newForce);
   emit forceChangedOld(newForce);
}

void Settings::Simulation::onWindowResized(int width, int height)
{
   updateGridCellSize(width, height);
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
   emit recomputeVertexPositions(QSize(width, height), cellSize);
}
