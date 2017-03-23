#ifndef HUECOLORMAP_H
#define HUECOLORMAP_H

#include "colormaps/abstractcolormap.h"


class HueColorMap : public AbstractColorMap
{
   public:
      static AbstractColorMap *Create(int numColors, float saturation, float hue);

   private:
      HueColorMap(int numColors, float saturation, float hue);
      void fill();
};

#endif // HUECOLORMAP_H
