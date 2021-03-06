#ifndef SETTINGSNS_H
#define SETTINGSNS_H

#include "colormaps/colormapfactory.h"
#include "QSize"
#include <limits>
#include "utilities/rotation.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif



namespace Settings {
    class Simulation;
    const Simulation& simulation();

    class Canvas;
    const Canvas& canvas();

    namespace visualization {
        QStringList getScalarVariableNames();

        QStringList getAllVectorVariableNames();

        QStringList getNonDerivedVectorVariableNames();

        QStringList getGlyphNames();

        class ColorMap;

        class Smoke;
        const Smoke& smoke();

        class Glyphs;
        const Glyphs& glyphs();

        class StreamLines;
        const StreamLines& streamLines();

        class StreakSurface;
        const StreakSurface& streakSurface();

        class Slices;
        const Slices& slices();
    }

    namespace sim {
        enum Scalar
        {
           fluidDensity,
           fluidVelocityMagnitude,
           forceFieldMagnitude
        };

        enum Vector
        {
           fluidVelocity,
           force,
           fluidDensityGradient,
           fluidVelocityMagnitudeGradient
        };

        enum GlyphsType
        {
           hedgehog,
           triangles,
           airplane,
           cone,
        };
    }

    namespace engines {
        enum EnginesTypes
        {
           smoke,
           glyphs,
           seedCurve,
           streakObjects,
           seedPoints,
           streamLines,

           //Slice engines
           smokeSlices,
           glyphSlices,
           streamLineSlices,

           numberOfEngines
        };
    }

    namespace defaults {
        namespace simulation {
            static const float valueRangeMin = 0.0f;
            static const float valueRangeMax = 10.0f;

            static const int forceMin = 1;
            static const int forceMax = 100;
        }

        namespace canvas {
            static const double scalingFactor = 1.0;
            static const QVector3D panningPosition(0.0, 0.0, 0.0);
            static const Rotation rotation;
        }

        namespace visualization {
            namespace colormap {
                static const ColorMapFactory::colorMaps colormap = ColorMapFactory::colorMaps::rainbow;
                static const float clampMin = 0.0f;
                static const float clampMax = 1.0f;
                static const bool clampingOn = false;
                static const float clampEpsilon = 0.0001;
                static const Settings::sim::Scalar scalar = Settings::sim::fluidDensity;

                static const int numColors = 256;
                static const int minNumColors = 2;
                static const int maxNumColors = 256;
                static const float saturation = 1.0f;
                static const float minSaturation = 0.0f;
                static const float maxSaturation = 1.0f;
            }
        }

        namespace engines {
            static const bool activeEngines[9] =
            {
               //Smoke
               true,
               //Glyphs
               false,
               //Stream Surfaces
               false,false,
               //StreamLines
               false,false,

               //Slice Engines
               false,false, false
            };
        }
    }
}

#endif // SETTINGSNS_H
