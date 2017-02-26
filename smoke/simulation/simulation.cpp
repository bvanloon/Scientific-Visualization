#include "simulation.h"

#include "settings/settings.h"
#include "settings/simulationsettings.h"
#include "settings/canvassettings.h"
#include "settings/visualizationsettings.h"

#include <QDebug>

Simulation::Simulation(QObject *parent) :
    QObject(parent),
    lastMousePosition(0.0f, 0.0f),
    grid(new UniformGrid(Settings::simulation().dimension))
{
    this->realization = new SimulationRealization();
}

Simulation::~Simulation()
{
    delete this->realization;
    delete this->grid;
}


QVector<QVector3D> Simulation::getGridVertices()
{
    QVector<QVector3D> gridVertices;
    int idx;
    QVector3D gridPoint;
    QVector3D offset;

    for (int i = 0; i < Settings::simulation().dimension; i++){
        for (int j = 0; j < Settings::simulation().dimension; j++)
        {
            idx = (j * Settings::simulation().dimension) + i;
            gridPoint = QVector3D(
                        Settings::simulation().cellSize.width() + (fftw_real)i * Settings::simulation().cellSize.width(),
                        Settings::simulation().cellSize.height() + (fftw_real)j * Settings::simulation().cellSize.height(),
                        0.0f);
            offset = QVector3D(
                        Settings::visualization().vectorScale * this->realization->vx[idx],
                        Settings::visualization().vectorScale * this->realization->vy[idx],
                        0.0f);
            gridVertices.append(gridPoint);
            gridVertices.append(gridPoint + offset);
        }
    }
    return gridVertices;
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

QVector<float> Simulation::getTexCoord(Simulation::textureCoordinateGetterSimple getter)
{
    QVector<float> textureCoordinates;
    float coordinate0, coordinate1, coordinate2, coordinate3;

    for (int j = 0; j < Settings::simulation().dimension - 1; j++)
    {
        for (int i = 0; i < Settings::simulation().dimension - 1; i++)
        {

            coordinate0 = (this->*getter)(i, j);
            coordinate1 = (this->*getter)(i, j + 1);
            coordinate2 = (this->*getter)(i + 1, j + 1);
            coordinate3 = (this->*getter)(i + 1, j);

            textureCoordinates.append(coordinate0);
            textureCoordinates.append(coordinate1);
            textureCoordinates.append(coordinate2);

            textureCoordinates.append(coordinate0);
            textureCoordinates.append(coordinate2);
            textureCoordinates.append(coordinate3);
        }
    }
    return textureCoordinates;
}

QVector<float> Simulation::getTexCoordFluidDensity()
{
    return getTexCoord(&Simulation::getFluidDensityAt);
}

QVector<float> Simulation::getTexCoordFluidVelocityMagnitude()
{
    return getTexCoord(&Simulation::getFluidVelocityMagnitudeAt);
}

QVector<float> Simulation::getTexCoordForceFieldMagnitude()
{
    return getTexCoord(&Simulation::getForceMagnitudeAt);
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
    this->grid = new UniformGrid(Settings::simulation().dimension);
}

int Simulation::to1DIndex(int i, int j)
{
    return (j * Settings::simulation().dimension) + i;
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

float Simulation::getFluidVelocityMagnitudeAt(int i, int j)
{
    int idx = to1DIndex(i,j);
    return getFluidVelocityMagnitudeAt(idx);
}

float Simulation::getFluidVelocityMagnitudeAt(int idx)
{
    return getFluidVelocityAt(idx).length();
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

float Simulation::getForceMagnitudeAt(int i, int j)
{
    return getForceAt(i, j).length();
}

float Simulation::getForceMagnitudeAt(int idx)
{
    return getForceAt(idx).length();
}
