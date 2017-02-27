#include "colormapfactory.h"

#include <QStringList>
#include <QDebug>


ColorMapFactory::ColorMapFactory()

{
    registerColorMap(ColorMapFactory::colorMaps::rainbow, &RainbowColorMap::Create);
    registerColorMap(ColorMapFactory::colorMaps::grayScale , &GrayScaleColorMap::Create);
    registerColorMap(ColorMapFactory::colorMaps::heat, &HeatColorMap::Create);
    registerColorMap(ColorMapFactory::colorMaps::cold, &Coldcolormap::Create);
    registerColorMap(ColorMapFactory::colorMaps::zebra, &ZebraMap::Create);
}

ColorMapFactory::~ColorMapFactory()
{

}

QStringList ColorMapFactory::getColorMapNames()
{
    QStringList colormapNamesList;

   colormapNamesList << "Rainbow" << "Hot" << "Cold" << "Grayscale" << "Zebra" ;

    return colormapNamesList;
}

void ColorMapFactory::registerColorMap(const ColorMapFactory::colorMaps colormap, CreateColorMapFn pfnCreate)
{
    colorMapMapping[colormap] = pfnCreate;
}

AbstractColorMap *ColorMapFactory::createColorMap(const ColorMapFactory::colorMaps colormap, int numColors, float saturation)
{
    static AbstractColorMap* currentColormap;
    std::map<colorMaps, CreateColorMapFn>::iterator it = colorMapMapping.find(colormap);
    if( it != colorMapMapping.end() )
    {
        CreateColorMapFn fpn = it->second;
        currentColormap = fpn(numColors, saturation);
        return currentColormap;
    }
    return NULL;
}
