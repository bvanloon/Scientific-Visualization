#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "glyphs/abstractglyph.h"


class Triangle : public AbstractGlyph
{
   public:
      Triangle(QVector3D position, QVector3D direction, float scalar);

private:
      QVector3D computeOrthogonalVector(QVector3D vector);
};

#endif // TRIANGLE_H
