#include "simulationsettings.h"
#include "settings/canvassettings.h"
#include "fftw.h"
#include <QDebug>

Settings::Simulation::Simulation(QObject *parent) :
   QObject(parent),
   dimension(100),
   timestep(0.4),
   frozen(false),
   force(10.0f),
   cellSize(-1, -1),
   useDynamicValueRange(true)
{
   staticScalarRanges.insert(Settings::sim::Scalar::fluidDensity, Range<double>(0.0f, force));
   staticScalarRanges.insert(Settings::sim::Scalar::fluidVelocityMagnitude, Range<double>(0.0f, 0.1f));
   staticScalarRanges.insert(Settings::sim::Scalar::forceFieldMagnitude, Range<double>(0.0f, 0.5f));

   dynamicScalarRanges.insert(Settings::sim::Scalar::fluidDensity, Range<double>(0.0f, force));
   dynamicScalarRanges.insert(Settings::sim::Scalar::fluidVelocityMagnitude, Range<double>(0.0f, 0.1f));
   dynamicScalarRanges.insert(Settings::sim::Scalar::forceFieldMagnitude, Range<double>(0.0f, 0.5f));
}

const Settings::Simulation& Settings::Simulation::instance()
{
   static Simulation instance;

   return instance;
}

void Settings::Simulation::updateRange(Settings::sim::Scalar scalar, QMultiMap<Settings::sim::Scalar, Range<double> > *rangeList, float minimum, float maximum)
{
   Range<double> range = rangeList->find(scalar).value();
   range.change(minimum, maximum);
   rangeList->replace(scalar, range);
}

void Settings::Simulation::updateStaticRange(Settings::sim::Scalar scalar, float minimum, float maximum)
{
   updateRange(scalar, &staticScalarRanges, minimum, maximum);
   if (!useDynamicValueRange) emit valueRangeChanged(scalar, minimum, maximum);
}

void Settings::Simulation::updateDynamicRange(Settings::sim::Scalar scalar, float minimum, float maximum)
{
   updateRange(scalar, &dynamicScalarRanges, minimum, maximum);
   if (useDynamicValueRange) emit valueRangeChanged(scalar, minimum, maximum);
}

Range<double> Settings::Simulation::getRange(Settings::sim::Scalar scalar) const
{
   if (useDynamicValueRange) return dynamicScalarRanges.constFind(scalar).value();
   else return staticScalarRanges.constFind(scalar).value();
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
      qDebug() << "Settings::visualization::Glyphs::getCurrentMagnitudeRange(): Currently gradient magnitudes are not supported. ";
      exit(-1);
   }
}

void Settings::Simulation::onUseDynamicValueRangeToggled(bool toggle)
{
   useDynamicValueRange = toggle;

   emitRange(Settings::sim::Scalar::fluidDensity);
   emitRange(Settings::sim::Scalar::fluidVelocityMagnitude);
   emitRange(Settings::sim::Scalar::forceFieldMagnitude);
}

void Settings::Simulation::onUpdateDynamicRange(Settings::sim::Scalar scalar, Range<double> range)
{
   updateDynamicRange(scalar, range.minimum(), range.maximum());
}

void Settings::Simulation::emitRange(Settings::sim::Scalar scalar)
{
   Range<double> range = getRange(scalar);
   emit valueRangeChanged(scalar, range.minimum(), range.maximum());
}

void Settings::Simulation::onDimensionChanged(int newDimension)
{
   this->dimension = newDimension;
   updateGridCellSize();
}

void Settings::Simulation::onForceChanged(float newForce)
{
   this->force = newForce;
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

void Settings::Simulation::onAllConnectionsAreSetUp()
{
   onUseDynamicValueRangeToggled(useDynamicValueRange);
}

void Settings::Simulation::onUpdateStaticRangesToDynamicRanges()
{
   updateStaticRangeToDynamicRange(Settings::sim::Scalar::fluidDensity);
   updateStaticRangeToDynamicRange(Settings::sim::Scalar::fluidVelocityMagnitude);
   updateStaticRangeToDynamicRange(Settings::sim::Scalar::forceFieldMagnitude);
}

void Settings::Simulation::updateStaticRangeToDynamicRange(Settings::sim::Scalar scalar)
{
   Range<double> range = getDynamicRange(scalar);
   updateStaticRange(scalar, range.minimum(), range.maximum());
}

Range<double> Settings::Simulation::getDynamicRange(Settings::sim::Scalar scalar)
{
   return dynamicScalarRanges.constFind(scalar).value();
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
