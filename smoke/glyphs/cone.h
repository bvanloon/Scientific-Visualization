#ifndef CONE_H
#define CONE_H

#include "glyphs/abstractglyph.h"

class Cone : public AbstractGlyph
{
public:
    Cone(QVector3D position, QVector3D direction, float scalar);
};

#endif // CONE_H
