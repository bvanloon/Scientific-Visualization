#include "simulation.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

#include <QDebug>

Simulation::Simulation(QObject *parent) :
    QObject(parent),
    lastMousePosition(0.0f, 0.0f)
{
    this->realization = new SimulationRealization();
    this->simulationGrid = UniformGrid::createSimulationGrid(Settings::simulation().dimension, Settings::canvas().size, this->realization);
    this->visualizationGrid = UniformGrid::createVisualizationGrid(5, Settings::canvas().size, this->simulationGrid);
}

Simulation::~Simulation()
{
    delete realization;
    delete simulationGrid;
    delete visualizationGrid;
}


QVector<QVector3D> Simulation::getSimpleHedgeHodges()
{
    QVector<QVector3D> hedgeHodgeVertices(simulationGrid->numVertices() * 2);
    QVector<Vertex*>::const_iterator currentVertex = simulationGrid->getVertices().begin();
    QVector3D position;
    for(int i = 0; currentVertex != simulationGrid->getVertices().end(); currentVertex++){
        position = *((*currentVertex)->getPosition());
        hedgeHodgeVertices[i++] = position;
        hedgeHodgeVertices[i++] = position +
                Settings::visualization().vectorScale * QVector3D((*currentVertex)->getFluidVelocity(), 0.0f);
    }
    return hedgeHodgeVertices;
}

Triangulation Simulation::getGridTriangulation()
{
    return simulationGrid->getTriangulation();
}

QVector<float> Simulation::getTexCoord(Vertex::scalarGetter getter, Triangulation triangulation)
{
    QVector<float> textureCoordinates;
    Vertex* vertex;
    for(int i = 0; i < triangulation.numVertices(); i++){
        vertex = triangulation.getVertices().at(i);
        textureCoordinates.append((vertex->*getter)());
    }
    return textureCoordinates;
}

QVector<float> Simulation::getTexCoordFluidDensity(Triangulation triangulation)
{
    return getTexCoord(&Vertex::getFluidDensity, triangulation);
}

QVector<float> Simulation::getTexCoordFluidVelocityMagnitude(Triangulation triangulation)
{
    return getTexCoord(&Vertex::getFluidVelocityMagnitude, triangulation);
}

QVector<float> Simulation::getTexCoordForceFieldMagnitude(Triangulation triangulation)
{
    return getTexCoord(&Vertex::getForceMagnitude, triangulation);
}

void Simulation::step()
{
    this->realization->do_one_simulation_step();
}

void Simulation::onMouseMoved(QPoint newPosition)
{
    //Invert y-position
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
    simulationGrid->changeGridArea(QSizeF(width, height));
    visualizationGrid->changeGridArea(QSizeF(width, height), simulationGrid->getPadding());
}
