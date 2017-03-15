#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QVector3D>
#include "glyphs/abstractglyph.h"

class Airplane : public AbstractGlyph
{
public:
    Airplane(QVector3D position, QVector3D direction, float scalar);
};

#endif // AIRPLANE_H
