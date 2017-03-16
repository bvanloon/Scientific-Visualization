#ifndef CONE_H
#define CONE_H

#include "glyphs/abstractglyph.h"
#include "utilities/mesh.h"

class Cone : public AbstractGlyph
{
public:
    Cone(QVector3D position, QVector3D direction, float scalar);

    static const mesh::TriangleMesh* unitCone;

private:
    mesh::TriangleMesh* cone;

    static const double maxCellRatio;

    float computeScalingFactor(float magnitude);

    void translate(QVector3D position);
    void scale(float scalingFactor);
    void rotate(QVector3D direction);
};

#endif // CONE_H
