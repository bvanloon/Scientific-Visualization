#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>
#include <QVector>
#include <QVector3D>

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);

    QVector<QVector3D> getVertices();
    QVector<QVector3D> getColors();

signals:

public slots:

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
};

#endif // SMOKE_H
