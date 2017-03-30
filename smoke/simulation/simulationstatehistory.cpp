#include "simulationstatehistory.h"

SimulationStateHistory::SimulationStateHistory(QObject *parent) :
   QObject(parent),
   QQueue(QQueue<StateGrid>())
{}

const SimulationStateHistory& SimulationStateHistory::instance()
{
    static SimulationStateHistory instance;

    return instance;
}
