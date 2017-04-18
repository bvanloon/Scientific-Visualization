#include "colormapfactory.h"

#include <QStringList>
#include <QDebug>


ColorMapFactory::ColorMapFactory()

{
   registerColorMap(ColorMapFactory::colorMaps::rainbow, &RainbowColorMap::Create);
   registerColorMap(ColorMapFactory::colorMaps::grayScale, &GrayScaleColorMap::Create);
   registerColorMap(ColorMapFactory::colorMaps::heat, &HeatColorMap::Create);
   registerColorMap(ColorMapFactory::colorMaps::cold, &Coldcolormap::Create);
   registerColorMap(ColorMapFactory::colorMaps::zebra, &ZebraMap::Create);
   registerColorMap(ColorMapFactory::colorMaps::hue, &HueColorMap::Create);
   registerColorMap(ColorMapFactory::colorMaps::diverging, &Diverging::Create);
}

ColorMapFactory::~ColorMapFactory()
{}

QStringList ColorMapFactory::getColorMapNames()
{
   QStringList colormapNamesList;

   colormapNamesList << "Rainbow" << "Hot" << "Cold" << "Grayscale" << "Zebra" << "Hue" << "Diverging";

   return colormapNamesList;
}

void ColorMapFactory::registerColorMap(const ColorMapFactory::colorMaps colormap, CreateColorMapFn pfnCreate)
{
   colorMapMapping[colormap] = pfnCreate;
}

AbstractColorMap *ColorMapFactory::createColorMap(const ColorMapFactory::colorMaps colormap, int numColors, float saturation, float hue)
{
   static AbstractColorMap *currentColormap;

   std::map<colorMaps, CreateColorMapFn>::iterator it = colorMapMapping.find(colormap);
   if (it != colorMapMapping.end())
   {
      CreateColorMapFn fpn = it->second;
      currentColormap = fpn(numColors, saturation, hue);
      return currentColormap;
   }
   return NULL;
}
