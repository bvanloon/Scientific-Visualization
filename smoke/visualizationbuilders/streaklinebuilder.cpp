#include "streaklinebuilder.h"
#include "simulation/simulationstatehistory.h"

StreakLineBuilder::StreakLineBuilder(QVector3D currentPosition,
                                     const Settings::visualization::StreamObject *configuration) :
   StreamLineBuilder(SimulationHistory::getSimulationGridAtQueueIdx(0), currentPosition, configuration)
{
   qDebug() << "StreakLineBuilder::StreakLineBuilder";
}
