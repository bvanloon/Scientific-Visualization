#include "simulation.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"

#include <QDebug>

Simulation::Simulation(QObject *parent) :
   QObject(parent),
   realization(new SimulationRealization),
   grid(new SimulationGrid(
           Settings::simulation().dimension,
           Settings::canvas().size,
           realization->getData())),
   lastMousePosition(0.0f, 0.0f)
{
   connectToSettings();
}

Simulation::~Simulation()
{
   delete realization;
   delete grid;
}

void Simulation::step()
{
   this->realization->do_one_simulation_step();
   emit newSimulationState(new SimulationData(*(this->grid->getData())));
   emit newSimulationState();
   emitUpdatesOfDynamicRanges();
}

void Simulation::emitUpdatesOfDynamicRanges()
{
   emit updateDynamicRange(Settings::sim::fluidDensity, realization->getCurrentFluidDensityRange());
   emit updateDynamicRange(Settings::sim::fluidVelocityMagnitude, realization->getCurrentFluidVelocityMagnitudeRange());
   emit updateDynamicRange(Settings::sim::forceFieldMagnitude, realization->getCurrentForceFieldMagnitudeRange());
}

void Simulation::onMouseMoved(QPoint newPosition)
{
   newPosition = Settings::canvas().convertToNormalCoordinates(newPosition);

   this->realization->addForceAt(newPosition, this->lastMousePosition);
   this->lastMousePosition = newPosition;
}

void Simulation::onStep()
{
   this->step();
}

void Simulation::onWindowResized(int width, int height)
{
   grid->changeGridArea(QSizeF(width, height));
}

void Simulation::connectToSettings()
{
   connect(this, SIGNAL(updateDynamicRange(Settings::sim::Scalar,Range<double> )),
            &Settings::simulation(), SLOT(onUpdateDynamicRange(Settings::sim::Scalar,Range<double> )));
}

SimulationGrid *Simulation::getSimulationGrid() const
{
   return grid;
}
