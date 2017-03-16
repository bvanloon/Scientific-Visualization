#ifndef GLYPHS_CONE_H
#define GLYPHS_CONE_H

#include "glyphs/abstractglyph.h"
#include "utilities/mesh.h"

class Cone : public AbstractGlyph
{
public:
    Cone(QVector3D position, QVector3D direction, float scalar);

private:

    mesh::TriangleMesh* mesh;

    static const double maxCellRatio;

    float computeScalingFactor(QVector3D direction);

    void transform(QVector3D position, QVector3D direction);
    QMatrix4x4 translate(QVector3D position);
    QMatrix4x4 scale(QVector3D direction);
    QMatrix4x4 rotate(QVector3D direction);
};

#endif // GLYPHS_CONE_H
