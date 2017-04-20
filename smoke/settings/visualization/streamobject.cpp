#include "streamobject.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"
#include <QDebug>
#include <limits>

Settings::visualization::StreamObject::StreamObject(QObject *parent) :
   QObject(parent),
   timeStep(1.0),
   maximumTime(100),
   minimumMagnitude(0.004),
   vectorField(Settings::sim::Vector::fluidVelocity),
   vectorFieldMagnitude(determineMagnitudeGetter(vectorField)),
   //Private
   edgeLengthFactor(0.33),
   totalLengthFactor(std::numeric_limits<double>::infinity())
{
   //Initial cellsize is -1, which doesn't make sense.
   this->edgeLength = 4.0;
   this->totalLength = 4.0;

   this->getVector = Vertex::getVectorGetter(vectorField);
   this->getMagnitude = Vertex::getScalarGetter(vectorFieldMagnitude);
   connectToOtherSettings();
}

void Settings::visualization::StreamObject::ontimeStepChanged(double newTimeStep)
{
   this->timeStep = newTimeStep;
   emit clearCache();
}

void Settings::visualization::StreamObject::onMaximumTimeChanged(double newMaximumTime)
{
   this->maximumTime = newMaximumTime;
   emit clearCache();
}

void Settings::visualization::StreamObject::onEdgeLengthFactorChanged(double newEdgeLengthFactor)
{
   this->edgeLength = computeEdgeLength(newEdgeLengthFactor, Settings::simulation().cellSize.width());
   this->edgeLengthFactor = newEdgeLengthFactor;
   emit clearCache();
}

void Settings::visualization::StreamObject::onMaximumTotalLengthFactorChanged(double newValue)
{
   this->totalLength = computeMaximumTotalLength(newValue, Settings::simulation().cellSize.width());
   this->totalLengthFactor = newValue;
   emit clearCache();
}

void Settings::visualization::StreamObject::onCellSizeChanged(QSizeF currentCellSize)
{
   this->edgeLength = computeEdgeLength(this->edgeLengthFactor, currentCellSize.width());
   this->totalLength = computeMaximumTotalLength(this->totalLengthFactor, currentCellSize.width());
}

void Settings::visualization::StreamObject::connectToOtherSettings()
{
   connect(&Settings::simulation(), SIGNAL(cellSizeChanged(QSizeF)),
            this, SLOT(onCellSizeChanged(QSizeF)));
}

double Settings::visualization::StreamObject::getTotalLengthFactor() const
{
   return totalLengthFactor;
}

double Settings::visualization::StreamObject::getEdgeLengthFactor() const
{
   return edgeLengthFactor;
}

double Settings::visualization::StreamObject::computeEdgeLength(double factor, double cellSize)
{
   return factor * cellSize;
}

double Settings::visualization::StreamObject::computeMaximumTotalLength(double factor, double cellSize)
{
   return factor * cellSize;
}

Settings::sim::Scalar Settings::visualization::StreamObject::determineMagnitudeGetter(Settings::sim::Vector vectorField)
{
   Settings::sim::Scalar scalar;
   switch (vectorField)
   {
   case Settings::sim::Vector::fluidVelocity:
      scalar = Settings::sim::Scalar::fluidVelocityMagnitude;
      break;

   case Settings::sim::Vector::force:
      scalar = Settings::sim::Scalar::forceFieldMagnitude;
      break;

   case Settings::sim::Vector::fluidDensityGradient:
      qDebug() << "There is no magnitudegetter for fluidDensityGradient, returing the fluidDensity.";
      scalar = Settings::sim::fluidDensity;
      break;

   case Settings::sim::Vector::fluidVelocityMagnitudeGradient:
      qDebug() << "There is no magnitudegetter for fluidVelocityMagnitudeGradient, returing the forceFieldMagnitude.";
      scalar = Settings::sim::fluidVelocityMagnitude;
      break;
   }
   return scalar;
}
