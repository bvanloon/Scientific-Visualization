#include "streaklinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreakLineBuilder::StreakLineBuilder(QVector3D currentPosition,
                                     const Settings::visualization::StreamObject *configuration) :
   StreamLineBuilder(&SimulationHistory::instance().getSimulationGridAtQueueIdx(0),
                     currentPosition,
                     configuration)
{}

bool StreakLineBuilder::isMagnitudeLargeEnough(float magnitude)
{
   return true;
}

QVector3D StreakLineBuilder::integrate(QVector3D previousPosition)
{
   QVector3D nextPosition = previousPosition + QVector3D(10, 10, 10);
   return nextPosition;
}
