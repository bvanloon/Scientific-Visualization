#include "simulation.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

#include <QDebug>

Simulation::Simulation(QObject *parent) :
   QObject(parent),
   realization(new SimulationRealization),
   lastMousePosition(0.0f, 0.0f),
   grid(new SimulationGrid(
           Settings::simulation().dimension,
           Settings::canvas().size,
           realization->getData()))
{}

Simulation::~Simulation()
{
   delete realization;
   delete grid;
}

GlyphData Simulation::getGlyphData()
{
   return getGlyphData(grid);
}

GlyphData Simulation::getGlyphData(Grid *grid)
{
   return grid->getGlyphData();
}

Triangulation Simulation::getGridTriangulation()
{
   return grid->getTriangulation();
}

QVector<float> Simulation::getTexCoord(Vertex::scalarGetter getter, Triangulation triangulation)
{
   QVector<float> textureCoordinates;
   Vertex *vertex;

   for (int i = 0; i < triangulation.numVertices(); i++)
   {
      vertex = triangulation.getVertices().at(i);
      textureCoordinates.append((vertex->*getter)());
   }
   return textureCoordinates;
}

QVector<float> Simulation::getTexCoordFluidDensity(Triangulation triangulation)
{
   return getTexCoord(&Vertex::getFluidDensity, triangulation);
}

QVector<float> Simulation::getTexCoordFluidVelocityMagnitude(
   Triangulation triangulation)
{
   return getTexCoord(&Vertex::getFluidVelocityMagnitude, triangulation);
}

QVector<float> Simulation::getTexCoordForceFieldMagnitude(
   Triangulation triangulation)
{
   return getTexCoord(&Vertex::getForceMagnitude, triangulation);
}

void Simulation::step()
{
   this->realization->do_one_simulation_step();
   emit newSimulationState(new SimulationData(*(this->grid->getData())));
}

void Simulation::onMouseMoved(QPoint newPosition)
{
   // Invert y-position
   newPosition.setY(Settings::canvas().size.height() - newPosition.y());

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

UniformGrid *Simulation::getSimulationGrid() const
{
   return grid;
}
