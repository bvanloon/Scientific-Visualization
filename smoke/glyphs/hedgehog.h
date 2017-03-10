#ifndef HEDGEHOG_H
#define HEDGEHOG_H

#include "glyphs/abstractglyph.h"

class HedgeHog : public AbstractGlyph
{
   public:
      HedgeHog();
      HedgeHog(QVector3D position, QVector3D direction, float scalar);
};

#endif // HEDGEHOG_H
