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

    static float magnitudeMin = 1.0f;
    static float magnitudeMax = 0.0f;

    int idx0, idx1, idx2, idx3;
    QVector2D vec0, vec1, vec2, vec3;

    for (int j = 0; j < Settings::simulation().dimension - 1; j++)
    {
        for (int i = 0; i < Settings::simulation().dimension - 1; i++)
        {
            idx0 = (j * Settings::simulation().dimension) + i;
            idx1 = ((j  + 1)* Settings::simulation().dimension) + i;
            idx2 = ((j  + 1)* Settings::simulation().dimension) + i + 1;
            idx3 = (j * Settings::simulation().dimension) + i + 1;

            vec0 = QVector2D(this->realization->vx[idx0],
                             this->realization->vy[idx0]);
            vec1 = QVector2D(this->realization->vx[idx1],
                             this->realization->vy[idx1]);
            vec2 = QVector2D(this->realization->vx[idx2],
                             this->realization->vy[idx2]);
            vec3 = QVector2D(this->realization->vx[idx3],
                             this->realization->vy[idx3]);

            textureCoordinates.append(vec0.length());
            textureCoordinates.append(vec1.length());
            textureCoordinates.append(vec2.length());

            textureCoordinates.append(vec0.length());
            textureCoordinates.append(vec2.length());
            textureCoordinates.append(vec3.length());
        }
    }
    return textureCoordinates;
}

QVector<float> Simulation::getTexCoordForceFieldMagnitude()
{
    QVector<float> textureCoordinates;
    qDebug() << "QVector<float> Simulation::getTextureCoordinatesForceField";
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



