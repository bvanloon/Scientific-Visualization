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
    this->grid = UniformGrid::createSimulationGrid(Settings::simulation().dimension, Settings::canvas().size);
}

Simulation::~Simulation()
{
    delete this->realization;
    delete this->grid;
}


QVector<QVector3D> Simulation::getSimpleHedgeHodges()
{
    QVector<QVector3D> hedgeHodgeVertices(grid->numVertices() * 2);
    QVector<Vertex*>::const_iterator currentVertex = grid->getVertices().begin();
    int simulationIdx = 0;
    QVector3D position;
    for(int i = 0; currentVertex != grid->getVertices().end(); currentVertex++){
        position = *((*currentVertex)->getPosition());
        hedgeHodgeVertices[i++] = position;
        hedgeHodgeVertices[i++] = position +
                Settings::visualization().vectorScale * QVector3D(this->realization->vx[simulationIdx], this->realization->vy[simulationIdx++], 0.0f);
    }
    return hedgeHodgeVertices;
}

QVector<QVector3D> Simulation::getGridTriangulation()
{
    QVector<QVector3D> gridTriangles;

    double px0, py0, px1, py1, px2, py2, px3, py3;

    for (int j = 0; j < Settings::simulation().dimension - 1; j++)
    {
        for (int i = 0; i < Settings::simulation().dimension - 1; i++)
        {
            px0 = Settings::simulation().cellSize.width() + (fftw_real)i * Settings::simulation().cellSize.width();
            py0 = Settings::simulation().cellSize.height() + (fftw_real)j * Settings::simulation().cellSize.height();

            px1 = Settings::simulation().cellSize.width() + (fftw_real)i * Settings::simulation().cellSize.width();
            py1 = Settings::simulation().cellSize.height()+ (fftw_real)(j + 1) * Settings::simulation().cellSize.height();

            px2 = Settings::simulation().cellSize.width() + (fftw_real)(i + 1) * Settings::simulation().cellSize.width();
            py2 = Settings::simulation().cellSize.height() + (fftw_real)(j + 1) * Settings::simulation().cellSize.height();

            px3 = Settings::simulation().cellSize.width() + (fftw_real)(i + 1) * Settings::simulation().cellSize.width();
            py3 = Settings::simulation().cellSize.height() + (fftw_real)j * Settings::simulation().cellSize.height();

            gridTriangles.append(QVector3D(px0,py0,0.0f) );
            gridTriangles.append(QVector3D(px1,py1,0.0f) );
            gridTriangles.append(QVector3D(px2,py2,0.0f) );

            gridTriangles.append(QVector3D(px0,py0,0.0f) );
            gridTriangles.append(QVector3D(px2,py2,0.0f) );
            gridTriangles.append(QVector3D(px3,py3,0.0f) );
        }
    }

    return gridTriangles;
}

QVector<float> Simulation::getTexCoord(Simulation::textureCoordinateGetterSimple getter, QVector<QVector3D> vertexPositions)
{
    QVector<float> textureCoordinates;
    for(int i = 0; i < vertexPositions.size(); i++){
        textureCoordinates.append((this->*getter)(vertexPositions.at(i)));
    }
    return textureCoordinates;
}

QVector<float> Simulation::getTexCoordFluidDensity(QVector<QVector3D> vertexPositions)
{
    return getTexCoord(&Simulation::getFluidDensityAt, vertexPositions);
}

QVector<float> Simulation::getTexCoordFluidVelocityMagnitude(QVector<QVector3D> vertexPositions)
{
    return getTexCoord(&Simulation::getFluidVelocityMagnitudeAt, vertexPositions);
}

QVector<float> Simulation::getTexCoordForceFieldMagnitude(QVector<QVector3D> vertexPositions)
{
    return getTexCoord(&Simulation::getForceMagnitudeAt, vertexPositions);
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
    delete this->grid;
    this->grid = UniformGrid::createSimulationGrid(Settings::simulation().dimension, QSizeF(width, height));
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
