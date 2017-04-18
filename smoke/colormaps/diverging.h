#ifndef DIVERGING_H
#define DIVERGING_H

#include "colormaps/abstractcolormap.h"

class Diverging : public AbstractColorMap
{
   public:
      static AbstractColorMap *Create(int numColors, float saturation, float UNUSED(hue));
   private:
      Diverging(int numColors, float saturation);

      void fill();

      QColor divergenceColor(float f, float fmid);
};

#endif // DIVERGING_H
