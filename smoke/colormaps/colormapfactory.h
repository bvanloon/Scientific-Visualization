#ifndef COLORMAPFACTORY_H
#define COLORMAPFACTORY_H

#include "abstractcolormap.h"
#include "rainbowcolormap.h"
#include "grayscalecolormap.h"
#include "heatcolormap.h"

class ColorMapFactory
{
public:
    enum colorMaps: int
    {
        rainbow,
        heat,
        grayScale
    };


    ~ColorMapFactory();

    static ColorMapFactory *get(){
        static ColorMapFactory instance;
        return &instance;
    }

    AbstractColorMap *createColorMap(const colorMaps colormap, int numColors);

private:
    typedef AbstractColorMap* (*CreateColorMapFn)(int);

    std::map<colorMaps,CreateColorMapFn > colorMapMapping;

    ColorMapFactory();
    ColorMapFactory(const ColorMapFactory &){}
    ColorMapFactory &operator = (const ColorMapFactory &) {return *this;}

    void registerColorMap(const colorMaps colormap, CreateColorMapFn pfnCreate);




};

#endif // COLORMAPFACTORY_H
