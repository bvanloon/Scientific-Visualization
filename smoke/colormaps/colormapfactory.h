#ifndef COLORMAPFACTORY_H
#define COLORMAPFACTORY_H


#include "abstractcolormap.h"
#include "rainbowcolormap.h"
#include "grayscalecolormap.h"
#include "heatcolormap.h"
#include "coldcolormap.h"
#include "zebramap.h"
#include "huecolormap.h"
#include "diverging.h"
#include "twocolorcolormap.h"



class ColorMapFactory
{
   public:
      enum colorMaps { rainbow, heat, cold, grayScale, zebra, hue, diverging, twocolor };

      ~ColorMapFactory();

      static ColorMapFactory *get()
      {
         static ColorMapFactory instance;

         return &instance;
      }

      static QStringList getColorMapNames();

      AbstractColorMap *createColorMap(const colorMaps colormap, int numColors, float saturation, float hue = no_hue);

   private:
      typedef AbstractColorMap * (*CreateColorMapFn)(int, float, float);

      std::map<colorMaps, CreateColorMapFn> colorMapMapping;

      ColorMapFactory();
      ColorMapFactory(const ColorMapFactory&) {}

      ColorMapFactory& operator =(const ColorMapFactory&) { return *this; }

      void registerColorMap(const colorMaps colormap, CreateColorMapFn pfnCreate);
};

#endif // COLORMAPFACTORY_H
