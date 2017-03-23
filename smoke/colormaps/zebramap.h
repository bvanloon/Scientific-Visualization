#ifndef ZEBRAMAP_H
#define ZEBRAMAP_H

#include "colormaps/abstractcolormap.h"

class ZebraMap : public AbstractColorMap
{
   public:
      static AbstractColorMap *Create(int numColors, float saturation, float UNUSED(hue));

   private:
      ZebraMap(int numColors, float saturation);
      void fill();
};

#endif // ZEBRAMAP_H
