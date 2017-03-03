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

    //    this->simulationGrid = UniformGrid::createSimulationGrid(3, QSize(676, 525), this->realization);
    //    this->visualizationGrid = UniformGrid::createVisualizationGrid(4, QSize(676, 525), this->simulationGrid);
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

QVector<float> Simulation::getTexCoord(Simulation::textureCoordinateGetterSimple getter, Triangulation triangulation)
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
    visualizationGrid->changeGridArea(QSizeF(width, height));
}

int Simulation::to1DIndex(int i, int j)
{
    return (j * Settings::simulation().dimension) + i;
}

int Simulation::to1DIndex(QVector3D position)
{
    int i = qRound((position.x() / Settings::simulation().cellSize.width()) - 1);
    int j = qRound((position.y() / Settings::simulation().cellSize.height()) - 1);
    return to1DIndex(i, j);
}

float Simulation::getFluidDensityAt(int i, int j)
{
    int idx = to1DIndex(i,j);
    return getFluidDensityAt(idx);
}

float Simulation::getFluidDensityAt(int idx)
{
    return this->realization->rho[idx];
}

float Simulation::getFluidDensityAt(QVector3D position)
{
    int idx = to1DIndex(position);
    return getFluidDensityAt(idx);
}

QVector2D Simulation::getFluidVelocityAt(int i, int j)
{
    int idx = to1DIndex(i,j);
    return getFluidVelocityAt(idx);
}

QVector2D Simulation::getFluidVelocityAt(int idx)
{
    return QVector2D(this->realization->vx[idx],
                     this->realization->vy[idx]);
}

QVector2D Simulation::getFluidVelocityAt(QVector3D position)
{
    int idx = to1DIndex(position);
    return getFluidVelocityAt(idx);
}

float Simulation::getFluidVelocityMagnitudeAt(int i, int j)
{
    int idx = to1DIndex(i,j);
    return getFluidVelocityMagnitudeAt(idx);
}

float Simulation::getFluidVelocityMagnitudeAt(int idx)
{
    return getFluidVelocityAt(idx).length();
}

float Simulation::getFluidVelocityMagnitudeAt(QVector3D position)
{
    return getFluidVelocityAt(position).length();
}

QVector2D Simulation::getForceAt(int i, int j)
{
    int idx = to1DIndex(i, j);
    return getForceAt(idx);
}

QVector2D Simulation::getForceAt(int idx)
{
    return QVector2D(this->realization->fx[idx],
                     this->realization->fy[idx]);
}

QVector2D Simulation::getForceAt(QVector3D position)
{
    int idx = to1DIndex(position);
    return getForceAt(idx);
}

float Simulation::getForceMagnitudeAt(int i, int j)
{
    return getForceAt(i, j).length();
}

float Simulation::getForceMagnitudeAt(int idx)
{
    return getForceAt(idx).length();
}

float Simulation::getForceMagnitudeAt(QVector3D position)
{
    return getForceAt(position).length();
}
