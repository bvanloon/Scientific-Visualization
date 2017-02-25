#include "simulation.h"

#include "settings/settings.h"
#include "settings/simulations.h"
#include "settings/canvass.h"
#include "settings/visualizations.h"

#include <QDebug>

Simulation::Simulation(QObject *parent) :
    QObject(parent), lastMousePosition(0.0f, 0.0f)
{
    this->realization = new SimulationRealization();
}

Simulation::~Simulation()
{
    delete this->realization;
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

QVector<float> Simulation::getTexCoordFluidDensity()
{
    QVector<float> textureCoordinates;

    int idx0, idx1, idx2, idx3;

    for (int j = 0; j < Settings::simulation().dimension - 1; j++)
    {
        for (int i = 0; i < Settings::simulation().dimension - 1; i++)
        {
            idx0 = (j * Settings::simulation().dimension) + i;
            idx1 = ((j  + 1)* Settings::simulation().dimension) + i;
            idx2 = ((j  + 1)* Settings::simulation().dimension) + i + 1;
            idx3 = (j * Settings::simulation().dimension) + i + 1;

            textureCoordinates.append(this->realization->rho[idx0] );
            textureCoordinates.append(this->realization->rho[idx1] );
            textureCoordinates.append(this->realization->rho[idx2] );

            textureCoordinates.append(this->realization->rho[idx0] );
            textureCoordinates.append(this->realization->rho[idx2] );
            textureCoordinates.append(this->realization->rho[idx3] );
        }
    }
    return textureCoordinates;
}

QVector<float> Simulation::getTexCoordFluidVelocityMagnitude()
{
    QVector<float> textureCoordinates;

    float velocity0, velocity1, velocity2, velocity3;

    for (int j = 0; j < Settings::simulation().dimension - 1; j++)
    {
        for (int i = 0; i < Settings::simulation().dimension - 1; i++)
        {
            velocity0 = getFluidVelocityMagnitudeAt(i, j);
            velocity1 = getFluidVelocityMagnitudeAt(i, j + 1);
            velocity2 = getFluidVelocityMagnitudeAt(i + 1, j + 1);
            velocity3 = getFluidVelocityMagnitudeAt(i + 1, j);

            textureCoordinates.append(velocity0);
            textureCoordinates.append(velocity1);
            textureCoordinates.append(velocity2);

            textureCoordinates.append(velocity0);
            textureCoordinates.append(velocity2);
            textureCoordinates.append(velocity3);
        }
    }
    return textureCoordinates;
}

QVector<float> Simulation::getTexCoordForceFieldMagnitude()
{
    QVector<float> textureCoordinates;
    QVector2D force0, force1, force2, force3;

    int idx0, idx1, idx2, idx3;

    static float minimum = 1000.0f;
    static float maximum = -1000.0f;

    for (int j = 0; j < Settings::simulation().dimension - 1; j++)
    {
        for (int i = 0; i < Settings::simulation().dimension - 1; i++)
        {
            idx0 = (j * Settings::simulation().dimension) + i;
            idx1 = ((j  + 1)* Settings::simulation().dimension) + i;
            idx2 = ((j  + 1)* Settings::simulation().dimension) + i + 1;
            idx3 = (j * Settings::simulation().dimension) + i + 1;

            force0 = QVector2D(this->realization->fx[idx0],
                               this->realization->fy[idx0]);

            force1 = QVector2D(this->realization->fx[idx1],
                               this->realization->fy[idx1]);

            force2 = QVector2D(this->realization->fx[idx2],
                               this->realization->fy[idx2]);

            force3 = QVector2D(this->realization->fx[idx3],
                               this->realization->fy[idx3]);

            textureCoordinates.append(force0.length());
            textureCoordinates.append(force1.length());
            textureCoordinates.append(force2.length());

            textureCoordinates.append(force0.length());
            textureCoordinates.append(force2.length());
            textureCoordinates.append(force3.length());
        }
    }

    minimum = std::min(minimum,
                   *std::min_element(textureCoordinates.constBegin(), textureCoordinates.constEnd()));
    maximum = std::max(maximum,
                   *std::max_element(textureCoordinates.constBegin(), textureCoordinates.constEnd()));
    qDebug() << "getTexCoordForceFieldMagnitude [" << minimum << ", " << maximum << "]";
    return textureCoordinates;
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

int Simulation::to1DIndex(int i, int j)
{
    return (j * Settings::simulation().dimension) + i;
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



