#ifndef SEEDCURVEENGINE_H
#define SEEDCURVEENGINE_H

#include "abstractengine.h"
#include "unused.h"

class SeedCurveEngine : public AbstractEngine
{
   public:
      SeedCurveEngine();

      void draw();

   private:
      void setColorMapClampingTo(bool UNUSED(clampingOn));
      void setColorMapValueRange(float UNUSED(min), float UNUSED(max));

      void drawEdges();
      void drawVertices();
};

#endif // SEEDCURVEENGINE_H
