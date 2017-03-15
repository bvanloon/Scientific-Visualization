#include "vector.h"
#include <QLineF>

QVector3D computeOrthogonalVector(QVector3D vector)
{
    QVector3D normalVector = vector.normalized();
    QLineF line = QLineF(0.0f, 0.0f,
                          normalVector.x(), normalVector.y());
    QLineF normalLine = line.normalVector();

    return QVector3D(normalLine.x2(), normalLine.y2(), 0.0f);
}
