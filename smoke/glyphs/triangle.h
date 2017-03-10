#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "glyphs/abstractglyph.h"


class Triangle : public AbstractGlyph
{
   public:
      Triangle(QVector3D position, QVector3D direction, float scalar);
};

#endif // TRIANGLE_H
