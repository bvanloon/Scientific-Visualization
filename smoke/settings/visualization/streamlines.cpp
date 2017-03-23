#include "streamlines.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"
#include <limits>

Settings::visualization::StreamLines::StreamLines(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   timeStep(1.0),
   maximumTime(std::numeric_limits<double>::infinity()),
   edgeLengthFactor(Settings::defaults::visualization::streamlines::edgeLengthFactor),
   totalLengthFactor(Settings::defaults::visualization::streamlines::totalLengthFactor)
{
   colorMap->onTextureVariableChanged(Settings::sim::Scalar::fluidVelocityMagnitude);
   this->edgeLength = computeEdgeLength(edgeLengthFactor, Settings::simulation().cellSize.width());
   this->totalLength = computeEdgeLength(totalLengthFactor, Settings::simulation().cellSize.width());
   connectToOtherSettings();
}

double Settings::visualization::StreamLines::computeEdgeLength(double factor, double cellSize)
{
   return factor * cellSize;
}

double Settings::visualization::StreamLines::computeMaximumTotalLength(double factor, double cellSize)
{
   return factor * cellSize;
}

void Settings::visualization::StreamLines::connectToOtherSettings()
{
   connect(&Settings::canvas(), SIGNAL(windowResized(QSizeF,QSizeF)),
            this, SLOT(onWindowResized(QSizeF,QSizeF)));
   connect(&Settings::simulation(), SIGNAL(cellSizeChanged(QSizeF)),
           this, SLOT(onCellSizeChanged(QSizeF)));
}

void Settings::visualization::StreamLines::transformSeedPoints(QMatrix4x4 transformationMatrix)
{
   int numSeedPoints = numberOfSeedPoints();
   QPointF seedPoint;

   while (numSeedPoints--)
   {
      seedPoint = this->seedPoints.takeFirst();
      seedPoint = transformationMatrix * seedPoint;
      this->seedPoints.append(seedPoint);
   }
}

const Settings::visualization::StreamLines& Settings::visualization::StreamLines::instance()
{
   static StreamLines instance;

   return instance;
}

int Settings::visualization::StreamLines::numberOfSeedPoints()
{
   return this->seedPoints.length();
}

void Settings::visualization::StreamLines::ontimeStepChanged(double newTimeStep)
{
   this->timeStep = newTimeStep;
}

void Settings::visualization::StreamLines::onMaximumTimeChanged(double newMaximumTime)
{
   this->maximumTime = newMaximumTime;
}

void Settings::visualization::StreamLines::onEdgeLengthFactorChanged(double newEdgeLengthFactor)
{
   this->edgeLength = computeEdgeLength(newEdgeLengthFactor, Settings::simulation().cellSize.width());
   this->edgeLengthFactor = newEdgeLengthFactor;
}

void Settings::visualization::StreamLines::onMaximumTotalLengthFactorChanged(double newValue)
{
   this->maximumTotalLength = computeMaximumTotalLength(newValue, Settings::simulation().cellSize.width());
   this->totalLengthFactor = newValue;
}

void Settings::visualization::StreamLines::onClearSeedPoints()
{
   this->seedPoints.clear();
}

void Settings::visualization::StreamLines::onSeedPointAdded(QPointF newSeedPoint)
{
   newSeedPoint.setY(Settings::canvas().size.height() - newSeedPoint.y());
   this->seedPoints.append(newSeedPoint);
}

void Settings::visualization::StreamLines::onWindowResized(QSizeF oldSize, QSizeF newSize)
{
   double xScale = newSize.width() / oldSize.width();
   double yScale = newSize.height() / oldSize.height();

   QMatrix4x4 transformationMatrix;

   transformationMatrix.scale(xScale, yScale, 0.0);
   transformSeedPoints(transformationMatrix);
}

void Settings::visualization::StreamLines::onCellSizeChanged(QSizeF currentCellSize)
{
   this->edgeLength = computeEdgeLength(this->edgeLengthFactor, currentCellSize.width());
   this->totalLength = computeMaximumTotalLength(this->totalLengthFactor, currentCellSize.width());
}
