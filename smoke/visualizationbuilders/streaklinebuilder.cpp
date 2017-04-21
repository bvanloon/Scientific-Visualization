#include "streaklinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreakLineBuilder::StreakLineBuilder(QVector3D currentPosition,
                                     const Settings::visualization::StreamObject *configuration, double zStep) :
   StreamLineBuilder(&SimulationHistory::instance().getSimulationGridAtQueueIdx(0),
                     currentPosition,
                     configuration),
   currentStateIdx(0),
   zStep(zStep)
{}

bool StreakLineBuilder::isMagnitudeLargeEnough(float UNUSED(magnitude))
{
   return true;
}

QVector3D StreakLineBuilder::integrate(QVector3D previousPosition)
{
   ++currentStateIdx;
   QVector3D nextPosition = StreamLineBuilder::integrate(previousPosition);
   nextPosition.setZ(computeZValue(currentStateIdx));
   moveToNextGrid();

   return nextPosition;
}

void StreakLineBuilder::moveToNextGrid()
{
   if (this->currentStateIdx < SimulationHistory::instance().size())
   {
      this->grid = &SimulationHistory::instance().getSimulationGridAtQueueIdx(currentStateIdx);
   }
   else terminate = true;
}

double StreakLineBuilder::computeZValue(int currentStateIdx)
{
   return currentStateIdx * zStep;
}
