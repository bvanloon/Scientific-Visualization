#ifndef COLDCOLORMAP_H
#define COLDCOLORMAP_H

#include "colormaps/abstractcolormap.h"

class Coldcolormap : public AbstractColorMap
{
   public:
      static AbstractColorMap *Create(int numColors, float saturation, float UNUSED(hue));

   private:
      Coldcolormap(int numColors, float saturation);

      void fill();

      QRgb toColdColor(float f);
};

#endif // COLDCOLORMAP_H
