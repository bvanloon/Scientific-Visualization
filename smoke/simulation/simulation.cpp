#include "simulation.h"
#include <QDebug>

Simulation::Simulation(Settings* settings, QObject *parent) :
    QObject(parent), lastMousePosition(0.0f, 0.0f)
{
    this->settings = settings;
    this->realization = new SimulationRealization(settings);

    gridVertices.append(QVector3D(800.0f, 400.0f, 0.0f));
    gridVertices.append(QVector3D(500.0f, 200.0, 0.0f));
    gridVertices.append(QVector3D(100.0f, 400.0f, 0.0f));

    colors.append(QVector3D(1.0f, 0.0f, 0.0f));
    colors.append(QVector3D(0.0f, 1.0f, 0.0f));
    colors.append(QVector3D(0.0f, 0.0f, 1.0f));
}

Simulation::~Simulation()
{
    delete this->realization;
}

QVector<QVector3D> Simulation::getVertices()
{
    return this->gridVertices;
}

QVector<QVector3D> Simulation::getColors()
{
    return this->colors;
}

QVector<QVector3D> Simulation::getGridVertices()
{
    QVector<QVector3D> gridVertices;
    int idx;
    QVector3D gridPoint;
    QVector3D offset;

    for (int i = 0; i < this->settings->simulation->dimension; i++){
        for (int j = 0; j < this->settings->simulation->dimension; j++)
        {
            idx = (j * this->settings->simulation->dimension) + i;
            gridPoint = QVector3D(
                        settings->grid->cellWidth + (fftw_real)i * settings->grid->cellWidth,
                        settings->grid->cellHeight + (fftw_real)j *settings->grid->cellHeight,
                        0.0f);
            offset = QVector3D(
                        this->settings->visualization->vecScale * this->realization->vx[idx],
                        this->settings->visualization->vecScale * this->realization->vy[idx],
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

    for (int j = 0; j < settings->simulation->dimension - 1; j++)
    {
        for (int i = 0; i < settings->simulation->dimension - 1; i++)
        {
            px0 = settings->grid->cellWidth + (fftw_real)i * settings->grid->cellWidth;
            py0 = settings->grid->cellHeight + (fftw_real)j * settings->grid->cellHeight;

            px1 = settings->grid->cellWidth + (fftw_real)i * settings->grid->cellWidth;
            py1 = settings->grid->cellHeight + (fftw_real)(j + 1) * settings->grid->cellHeight;

            px2 = settings->grid->cellWidth + (fftw_real)(i + 1) * settings->grid->cellWidth;
            py2 = settings->grid->cellHeight + (fftw_real)(j + 1) * settings->grid->cellHeight;

            px3 = settings->grid->cellWidth + (fftw_real)(i + 1) * settings->grid->cellWidth;
            py3 = settings->grid->cellHeight + (fftw_real)j * settings->grid->cellHeight;

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

QVector<float> Simulation::getTextureCoordinates()
{
    QVector<float> textureCoordinates;

    int idx0, idx1, idx2, idx3;

    for (int j = 0; j < settings->simulation->dimension - 1; j++)
    {
        for (int i = 0; i < settings->simulation->dimension - 1; i++)
        {
            idx0 = (j * this->settings->simulation->dimension) + i;
            idx1 = ((j  + 1)* this->settings->simulation->dimension) + i;
            idx2 = ((j  + 1)* this->settings->simulation->dimension) + i + 1;
            idx3 = (j * this->settings->simulation->dimension) + i + 1;

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



void Simulation::step()
{
    this->realization->do_one_simulation_step();
}

void Simulation::onMouseMoved(QPoint newPosition)
{
    //Invert y-position
    newPosition.setY(this->settings->canvas->height - newPosition.y());

    this->realization->addForceAt(newPosition, this->lastMousePosition);
    this->lastMousePosition = newPosition;

    this->gridVertices.clear();

    gridVertices.append(QVector3D(newPosition.x(),       newPosition.y(),      0.0f));
    gridVertices.append(QVector3D(newPosition.x() - 10,  newPosition.y() - 10, 0.0f));
    gridVertices.append(QVector3D(newPosition.x() + 10,  newPosition.y() - 10, 0.0f));

    emit simulationUpdated();
}



