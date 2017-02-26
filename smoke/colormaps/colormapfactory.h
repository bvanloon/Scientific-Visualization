#ifndef COLORMAPFACTORY_H
#define COLORMAPFACTORY_H


#include "abstractcolormap.h"
#include "rainbowcolormap.h"
#include "grayscalecolormap.h"
#include "heatcolormap.h"


class ColorMapFactory
{
public:
    enum colorMaps { rainbow, heat, grayScale };

    ~ColorMapFactory();

    static ColorMapFactory *get(){
        static ColorMapFactory instance;
        return &instance;
    }

    static QStringList getColorMapNames();

    AbstractColorMap *createColorMap(const colorMaps colormap, int numColors, float saturation);

private:
    typedef AbstractColorMap* (*CreateColorMapFn)(int, float);

    std::map<colorMaps,CreateColorMapFn > colorMapMapping;

    ColorMapFactory();
    ColorMapFactory(const ColorMapFactory &){}
    ColorMapFactory &operator = (const ColorMapFactory &) {return *this;}

    void registerColorMap(const colorMaps colormap, CreateColorMapFn pfnCreate);

};

#endif // COLORMAPFACTORY_H
