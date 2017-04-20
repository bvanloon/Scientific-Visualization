#ifndef DIVERGING_H
#define DIVERGING_H

#include "colormaps/abstractcolormap.h"
#include "unused.h"

class Diverging : public AbstractColorMap
{
   public:
      static AbstractColorMap *Create(int numColors, float saturation, float UNUSED(hue));

   private:
      Diverging(int numColors, float saturation);

      void fill();


      QRgb divergenceColor(float f, float fmid);
};

#endif // DIVERGING_H
