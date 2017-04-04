#include "simulationsettings.h"
#include "settings/canvassettings.h"
#include "fftw.h"
#include <QDebug>

Settings::Simulation::Simulation(QObject *parent) :
   QObject(parent),
   dimension(50),
   timestep(0.4),
   frozen(false),
   force(10.0f),
   cellSize(-1, -1)
{
   scalarRanges.insert(Settings::sim::Scalar::fluidDensity, Range<double>(0.0f, force));
   scalarRanges.insert(Settings::sim::Scalar::fluidVelocityMagnitude, Range<double>(0.0f, 0.1f));
   scalarRanges.insert(Settings::sim::Scalar::forceFieldMagnitude, Range<double>(0.0f, 0.5f));
}

void Settings::Simulation::updateRange(Settings::sim::Scalar scalar, float minimum, float maximum)
{
   Range<double> range = scalarRanges.find(scalar).value();
   range.change(minimum, maximum);
   scalarRanges.replace(scalar, range);
   emit valueRangeChanged(scalar, minimum, maximum);
}

const Settings::Simulation& Settings::Simulation::instance()
{
   static Simulation instance;

   return instance;
}

Range<double> Settings::Simulation::getRange(Settings::sim::Scalar scalar) const
{
   return this->scalarRanges.constFind(scalar).value();
}

Range<double> Settings::Simulation::getMagnitudeRange(Settings::sim::Vector vector) const
{
   switch (vector)
   {
   case Settings::sim::Vector::fluidVelocity:
      return Settings::simulation().getRange(Settings::sim::Scalar::fluidVelocityMagnitude);

   case Settings::sim::Vector::force:
      return Settings::simulation().getRange(Settings::sim::Scalar::forceFieldMagnitude);

   case Settings::sim::Vector::fluidDensityGradient:
   //fall through

   case Settings::sim::Vector::fluidVelocityMagnitudeGradient:
   //fall through
   default:
      qDebug() << "Settings::visualization::Glyphs::getCurrentMagnitudeRange(): Current gradient magnitudes are not supported. ";
      exit(-1);
   }
}

void Settings::Simulation::onDimensionChanged(int newDimension)
{
   this->dimension = newDimension;
   updateGridCellSize();
}

void Settings::Simulation::onForceChanged(float newForce)
{
   this->force = newForce;
   updateRange(Settings::sim::fluidDensity, 0.0f, newForce);
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

void Settings::Simulation::updateGridCellSize(int canvasWidth, int canvasHeight)
{
   cellSize.setHeight((fftw_real)canvasHeight / (fftw_real)(dimension + 1));
   cellSize.setWidth((fftw_real)canvasWidth / (fftw_real)(dimension + 1));
   emit recomputeVertexPositions(QSize(canvasWidth, canvasHeight), cellSize);
   emit cellSizeChanged(this->cellSize);
}
