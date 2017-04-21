#include "streaklinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreakLineBuilder::StreakLineBuilder(QVector3D currentPosition,
                                     const Settings::visualization::StreamObject *configuration, double zStep) :
   StreamLineBuilder(&SimulationHistory::instance().getSimulationGridAtQueueIdx(0),
                     currentPosition,
                     configuration),
   currentStateIdx(computeInitialStateIdx()),
   zStep(zStep)
{
   moveToGridAtIdx(currentStateIdx);
}

bool StreakLineBuilder::isMagnitudeLargeEnough(float UNUSED(magnitude))
{
   return true;
}

QVector3D StreakLineBuilder::integrate(QVector3D previousPosition)
{
   ++currentStateIdx;
   QVector3D nextPosition = StreamLineBuilder::integrate(previousPosition);
   nextPosition.setZ(computeZValue(currentStateIdx));
   moveToGridAtIdx(currentStateIdx);

   return nextPosition;
}

void StreakLineBuilder::moveToGridAtIdx(int idx)
{
   if (idx < SimulationHistory::instance().size())
   {
      this->grid = &SimulationHistory::instance().getSimulationGridAtQueueIdx(idx);
   }
   else terminate = true;
}

double StreakLineBuilder::computeZValue(int currentStateIdx)
{
   return currentStateIdx * zStep;
}

int StreakLineBuilder::computeInitialStateIdx()
{
   return qMax(SimulationHistory::instance().size() - static_cast<int>(configuration->maximumTime) - 1, 0);
}
