#include "streaklinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreakLineBuilder::StreakLineBuilder(QVector3D currentPosition,
                                     const Settings::visualization::StreamObject *configuration) :
   StreamLineBuilder(&SimulationHistory::instance().getSimulationGridAtQueueIdx(0),
                     currentPosition,
                     configuration),
   currentStateIdx(0)
{}

bool StreakLineBuilder::isMagnitudeLargeEnough(float UNUSED(magnitude))
{
   return true;
}

QVector3D StreakLineBuilder::integrate(QVector3D previousPosition)
{
   QVector3D nextPosition = StreamLineBuilder::integrate(previousPosition);
   nextPosition.setZ(++currentStateIdx);

   moveToNextGrid();

   return nextPosition;
}

void StreakLineBuilder::moveToNextGrid()
{
}
