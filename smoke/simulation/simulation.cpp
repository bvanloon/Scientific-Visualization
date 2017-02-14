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

QVector<QVector3D> Simulation::getGridV()
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
            qDebug() << "offset: " << offset;
            gridVertices.append(gridPoint);
            gridVertices.append(gridPoint + offset);
        }
    }
    qDebug() << "QVector<QVector3D> Simulation::getGridV()";
    qDebug() << gridVertices.at(0);
    return gridVertices;
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

