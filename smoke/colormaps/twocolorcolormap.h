#ifndef TWOCOLORCOLORMAP_H
#define TWOCOLORCOLORMAP_H

#include "colormaps/abstractcolormap.h"

class TwoColorColormap : public AbstractColorMap
{
   public:
      static AbstractColorMap *Create(int numColors, float saturation, float UNUSED(hue));
   private:
      TwoColorColormap(int numColors, float saturation);

      void fill();
      QRgb toColor(float f);
};

#endif // TWOCOLORCOLORMAP_H
